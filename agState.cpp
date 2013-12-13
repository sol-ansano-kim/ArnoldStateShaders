#include <ai.h>
#include <cstring>

extern AtNodeMethods* agVectorStateMtd;
extern AtNodeMethods* agColorStateMtd;
extern AtNodeMethods* agIntStateMtd;
extern AtNodeMethods* agFloatStateMtd;

node_loader
{
   if (i == 0)
   {
      node->name = "vector_state";
      node->node_type = AI_NODE_SHADER;
      node->output_type = AI_TYPE_VECTOR;
      node->methods = agVectorStateMtd;
      strcpy(node->version, AI_VERSION);
      return true;
   }
   else if (i == 1)
   {
      node->name = "float_state";
      node->node_type = AI_NODE_SHADER;
      node->output_type = AI_TYPE_FLOAT;
      node->methods = agFloatStateMtd;
      strcpy(node->version, AI_VERSION);
      return true;
   }
   else if (i == 2)
   {
      node->name = "color_state";
      node->node_type = AI_NODE_SHADER;
      node->output_type = AI_TYPE_RGB;
      node->methods = agColorStateMtd;
      strcpy(node->version, AI_VERSION);
      return true;
   }
   else if (i == 3)
   {
      node->name = "integer_state";
      node->node_type = AI_NODE_SHADER;
      node->output_type = AI_TYPE_INT;
      node->methods = agIntStateMtd;
      strcpy(node->version, AI_VERSION);
      return true;
   }
   else
   {
      return false;
   }
}
