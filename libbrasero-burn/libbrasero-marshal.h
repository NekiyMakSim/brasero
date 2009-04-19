
#ifndef __brasero_marshal_MARSHAL_H__
#define __brasero_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* INT:VOID (./libbrasero-marshal.list:1) */
extern void brasero_marshal_INT__VOID (GClosure     *closure,
                                       GValue       *return_value,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint,
                                       gpointer      marshal_data);

/* INT:INT (./libbrasero-marshal.list:2) */
extern void brasero_marshal_INT__INT (GClosure     *closure,
                                      GValue       *return_value,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint,
                                      gpointer      marshal_data);

/* INT:OBJECT,INT,INT (./libbrasero-marshal.list:3) */
extern void brasero_marshal_INT__OBJECT_INT_INT (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* INT:POINTER,BOOLEAN (./libbrasero-marshal.list:4) */
extern void brasero_marshal_INT__POINTER_BOOLEAN (GClosure     *closure,
                                                  GValue       *return_value,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint,
                                                  gpointer      marshal_data);

/* VOID:DOUBLE,DOUBLE,LONG (./libbrasero-marshal.list:5) */
extern void brasero_marshal_VOID__DOUBLE_DOUBLE_LONG (GClosure     *closure,
                                                      GValue       *return_value,
                                                      guint         n_param_values,
                                                      const GValue *param_values,
                                                      gpointer      invocation_hint,
                                                      gpointer      marshal_data);

G_END_DECLS

#endif /* __brasero_marshal_MARSHAL_H__ */
