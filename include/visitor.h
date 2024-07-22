#ifndef VISITOR_H
#define VISITOR_H

typedef struct  Visitor Visitor;

Visitor *create_visitor(int id, const char *name);
int visitor_check_in(const char *name);
void free_visitor(Visitor *visitor);

#endif // VISITOR_H