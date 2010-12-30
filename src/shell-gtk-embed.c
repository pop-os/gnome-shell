/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

#include "config.h"

#include "shell-embedded-window-private.h"

#include <gdk/gdkx.h>

enum {
   PROP_0,

   PROP_WINDOW
};

struct _ShellGtkEmbedPrivate
{
  ShellEmbeddedWindow *window;
};

G_DEFINE_TYPE (ShellGtkEmbed, shell_gtk_embed, CLUTTER_X11_TYPE_TEXTURE_PIXMAP);

static void shell_gtk_embed_set_window (ShellGtkEmbed       *embed,
                                        ShellEmbeddedWindow *window);

static void
shell_gtk_embed_on_window_destroy (GtkWidget     *object,
                                   ShellGtkEmbed *embed)
{
  shell_gtk_embed_set_window (embed, NULL);
}

static void
shell_gtk_embed_on_window_realize (GtkWidget     *widget,
                                   ShellGtkEmbed *embed)
{
  /* Here automatic=FALSE means to use CompositeRedirectManual.
   * That is, the X server shouldn't draw the window onto the
   * screen.
   */
  clutter_x11_texture_pixmap_set_window (CLUTTER_X11_TEXTURE_PIXMAP (embed),
                                         gdk_x11_window_get_xid (gtk_widget_get_window (widget)),
                                         FALSE);
}

static void
shell_gtk_embed_set_window (ShellGtkEmbed       *embed,
                            ShellEmbeddedWindow *window)
{

  if (embed->priv->window)
    {
      _shell_embedded_window_set_actor (embed->priv->window, NULL);

      g_object_unref (embed->priv->window);

      clutter_x11_texture_pixmap_set_window (CLUTTER_X11_TEXTURE_PIXMAP (embed),
                                             None,
                                             FALSE);

      g_signal_handlers_disconnect_by_func (embed->priv->window,
                                            (gpointer)shell_gtk_embed_on_window_destroy,
                                            embed);
      g_signal_handlers_disconnect_by_func (embed->priv->window,
                                            (gpointer)shell_gtk_embed_on_window_realize,
                                            embed);
    }

  embed->priv->window = window;

  if (embed->priv->window)
    {
      g_object_ref (embed->priv->window);

      _shell_embedded_window_set_actor (embed->priv->window, embed);

      g_signal_connect (embed->priv->window, "destroy",
                        G_CALLBACK (shell_gtk_embed_on_window_destroy), embed);
      g_signal_connect (embed->priv->window, "realize",
                        G_CALLBACK (shell_gtk_embed_on_window_realize), embed);

      if (gtk_widget_get_realized (GTK_WIDGET (window)))
        shell_gtk_embed_on_window_realize (GTK_WIDGET (embed->priv->window), embed);
    }

  clutter_actor_queue_relayout (CLUTTER_ACTOR (embed));
}

static void
shell_gtk_embed_set_property (GObject         *object,
                              guint            prop_id,
                              const GValue    *value,
                              GParamSpec      *pspec)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (object);

  switch (prop_id)
    {
    case PROP_WINDOW:
      shell_gtk_embed_set_window (embed, (ShellEmbeddedWindow *)g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
shell_gtk_embed_get_property (GObject         *object,
                              guint            prop_id,
                              GValue          *value,
                              GParamSpec      *pspec)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (object);

  switch (prop_id)
    {
    case PROP_WINDOW:
      g_value_set_object (value, embed->priv->window);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
shell_gtk_embed_get_preferred_width (ClutterActor *actor,
                                     float         for_height,
                                     float        *min_width_p,
                                     float        *natural_width_p)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (actor);

  if (embed->priv->window
      && gtk_widget_get_visible (GTK_WIDGET (embed->priv->window)))
    {
      GtkRequisition requisition;
      gtk_widget_size_request (GTK_WIDGET (embed->priv->window), &requisition);

      *min_width_p = *natural_width_p = requisition.width;
    }
  else
    *min_width_p = *natural_width_p = 0;
}

static void
shell_gtk_embed_get_preferred_height (ClutterActor *actor,
                                      float         for_width,
                                      float        *min_height_p,
                                      float        *natural_height_p)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (actor);

  if (embed->priv->window
      && gtk_widget_get_visible (GTK_WIDGET (embed->priv->window)))
    {
      GtkRequisition requisition;
      gtk_widget_size_request (GTK_WIDGET (embed->priv->window), &requisition);

      *min_height_p = *natural_height_p = requisition.height;
    }
  else
    *min_height_p = *natural_height_p = 0;
}

static void
shell_gtk_embed_paint (ClutterActor *actor)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (actor);
  float wx = 0.0, wy = 0.0, x, y, ax, ay;
  float w, h;

  CLUTTER_ACTOR_CLASS (shell_gtk_embed_parent_class)->paint (actor);

  if (!embed->priv->window)
    return;

  /* Move the X window to the same position as the actor; it's much
   * easier to just do this from paint() than it is to tray to track
   * the position and allocation of @embed and each of its ancestors
   * as they change. We don't use get_transformed_position() here
   * because we know that the icon isn't scaled or rotated, and so
   * it's faster to avoid the floating-point transformations.
   */
  clutter_actor_get_size (actor, &w, &h);
  while (actor)
    {
      clutter_actor_get_position (actor, &x, &y);
      clutter_actor_get_anchor_point (actor, &ax, &ay);

      wx += x - ax;
      wy += y - ay;

      actor = clutter_actor_get_parent (actor);
    }

  _shell_embedded_window_allocate (embed->priv->window,
                                   (int)(0.5 + wx), (int)(0.5 + wy),
                                   w, h);
}

static void
shell_gtk_embed_realize (ClutterActor *actor)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (actor);

  _shell_embedded_window_realize (embed->priv->window);

  CLUTTER_ACTOR_CLASS (shell_gtk_embed_parent_class)->realize (actor);
}

static void
shell_gtk_embed_unrealize (ClutterActor *actor)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (actor);

  _shell_embedded_window_unrealize (embed->priv->window);

  CLUTTER_ACTOR_CLASS (shell_gtk_embed_parent_class)->unrealize (actor);
}

static void
shell_gtk_embed_dispose (GObject *object)
{
  ShellGtkEmbed *embed = SHELL_GTK_EMBED (object);

  shell_gtk_embed_set_window (embed, NULL);

  G_OBJECT_CLASS (shell_gtk_embed_parent_class)->dispose (object);
}

static void
shell_gtk_embed_class_init (ShellGtkEmbedClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);

  g_type_class_add_private (klass, sizeof (ShellGtkEmbedPrivate));

  object_class->get_property = shell_gtk_embed_get_property;
  object_class->set_property = shell_gtk_embed_set_property;
  object_class->dispose      = shell_gtk_embed_dispose;

  actor_class->get_preferred_width = shell_gtk_embed_get_preferred_width;
  actor_class->get_preferred_height = shell_gtk_embed_get_preferred_height;
  actor_class->paint = shell_gtk_embed_paint;
  actor_class->realize = shell_gtk_embed_realize;
  actor_class->unrealize = shell_gtk_embed_unrealize;

  g_object_class_install_property (object_class,
                                   PROP_WINDOW,
                                   g_param_spec_object ("window",
                                                        "Window",
                                                        "ShellEmbeddedWindow to embed",
                                                        SHELL_TYPE_EMBEDDED_WINDOW,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

static void
shell_gtk_embed_init (ShellGtkEmbed *embed)
{
  embed->priv = G_TYPE_INSTANCE_GET_PRIVATE (embed, SHELL_TYPE_GTK_EMBED,
                                             ShellGtkEmbedPrivate);

  /* automatic here means whether ClutterX11TexturePixmap should
   * process damage update and refresh the pixmap itself.
   */
  clutter_x11_texture_pixmap_set_automatic (CLUTTER_X11_TEXTURE_PIXMAP (embed), TRUE);
}

/*
 * Public API
 */
ClutterActor *
shell_gtk_embed_new (ShellEmbeddedWindow *window)
{
  g_return_val_if_fail (SHELL_IS_EMBEDDED_WINDOW (window), NULL);

  return g_object_new (SHELL_TYPE_GTK_EMBED,
                       "window", window,
                       NULL);
}
