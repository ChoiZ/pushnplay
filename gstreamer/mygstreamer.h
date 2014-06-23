#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifndef _MYGSTREAMER_H
#define _MYGSTREAMER_H

#define HMS_TIME_FORMAT "u:%02u:%02u"

#define HMS_TIME_ARGS(t) \
        GST_CLOCK_TIME_IS_VALID (t) ? \
        (guint) (((GstClockTime)(t)) / (GST_SECOND * 60 * 60)) : 99, \
        GST_CLOCK_TIME_IS_VALID (t) ? \
        (guint) ((((GstClockTime)(t)) / (GST_SECOND * 60)) % 60) : 99, \
        GST_CLOCK_TIME_IS_VALID (t) ? \
        (guint) ((((GstClockTime)(t)) / GST_SECOND) % 60) : 99

enum interface_type {
  IFACE_ALSA,
  IFACE_PULSE,
  IFACE_JACK
};


/* Structure to contain all our information, so we can pass it around */
typedef struct _CustomData {
    GstElement *pipeline;           /* Our one and only pipeline */
    GstElement *audioconvert;
    GstElement *audioresample;
    GstElement *uridecodebin;
    GstElement *jackaudiosink;

    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *taglabel;
    GtkWidget *timelabel;
    GtkWidget *playPauseButton;
    GtkWidget *filechooser;
    GtkWidget *mainwindow;

    gchar *nextfile_uri;            /* URI of the next audio file/URL to play */
    gchar *last_folder_uri;         /* URI of the last selected folder */


    /* Config format */
    gchar *config_audio_uri;        /* file URI read from config file */
    gchar *config_button_text;      /* text to be shown from config file*/
    gchar *config_button_color;     /* desired color from config file */
    gchar *config_button_fg_color;      /* text color to be shown from config file*/


    gulong slider_update_signal_id; /* Signal ID for the slider update signal */

    gulong file_selection_signal_id;

    enum interface_type iface_type; /* Backend to use */


    GstState state;                 /* Current state of the pipeline */
    gint64 duration;                /* Duration of the clip, in nanoseconds */
    gboolean is_network_stream;	    /* Current URI might not be a local file */
    gboolean blink;                 /* Toggle state for the button */
} CustomData;

#endif /* _MYGSTREAMER_H */
