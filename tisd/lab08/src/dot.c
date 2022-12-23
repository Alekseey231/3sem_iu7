/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/dot.h"

#include <stdio.h>

void graph_export_to_dot_saved(FILE *f, char *graph_name, graph_t *graph, int edge)
{
    fprintf(f, "graph %s {\n", graph_name);
    fprintf(f, "rankdir=LR;\n");

    for(size_t i = 1; i < graph->count_edge; ++i)
    {
      if(edge == -1 || (int)i!=edge)
      {
        fprintf(f, "v%ld [label = \"%ld\"]\n", i, i);
      }
      else
      {
        fprintf(f, "v%ld [label = \"%ld\", style=\"filled\", color=\"black\", fillcolor=\"skyblue\"]\n", i, i);
      }
    }

    edge_t *buf = calloc(graph->count_edge * (graph->count_edge - 1), sizeof(edge_t));
    if(buf != NULL)
    {
      size_t count_elements = 0;
    for(size_t i = 0; i < graph->count_edge; ++i)
    {
      //printf("%ld\n", i);
      list_apply_dot((graph->adjacency_list)[i], node_to_dot_saved, f, i, buf, &count_elements);
    }
  }
  free(buf);
  char *str = "{ rank = sink;\n"
    "Legend [shape=none, margin=0, label=<\n"
    "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n"
     "<TR>\n"
      "<TD COLSPAN=\"2\"><B>Legend</B></TD>\n"
     "</TR>\n"
     "<TR>\n"
      "<TD>Авто</TD>\n"
      "<TD BGCOLOR=\"RED\"></TD>\n"
     "</TR>\n"
     "<TR>\n"
     " <TD>Жд</TD>\n"
     " <TD BGCOLOR=\"BLUE\"></TD>\n"
    " </TR>\n"
    "</TABLE>\n"
   ">];\n"
  "}\n";
  fprintf(f, "%s", str);
  fprintf(f, "}\n");
}

void node_to_dot_saved(node_t *node, void *param, size_t index)
{
    FILE *f = param;

    if (node->type == 0)
    {
        fprintf(f, "v%ld -- v%d [ label = %d,style=bold,color=red ];\n", index, node->dest, node->weight);
    }
    else
        fprintf(f, "v%ld -- v%d [ label = %d,style=bold,color=blue ];\n", index, node->dest, node->weight);
}
