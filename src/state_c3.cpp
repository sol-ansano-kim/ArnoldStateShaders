/*
MIT License

Copyright (c) 2016 Gaetan Guidet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "common.h"

AI_SHADER_NODE_EXPORT_METHODS(StateC3Mtd);

enum ColorStateParams
{
   p_state = 0
};

static const char* ColorStateNames[] =
{
   "light_intensity",
   "unoccluded_light_intensity",
   "shadow_occlusion",
   NULL
};

enum ColorState
{
   CS_Li = 0,
   CS_Liu,
   CS_Lo,
};

namespace SSTR
{
   extern AtString state;
   extern AtString linkable;
}

node_parameters
{
   AiParameterEnum(SSTR::state, CS_Li, ColorStateNames);
}

node_initialize
{
   AiNodeSetLocalData(node, AiMalloc(sizeof(int)));
}

node_update
{
   int *data = (int*) AiNodeGetLocalData(node);
   *data = AiNodeGetInt(node, SSTR::state);
}

node_finish
{
   AiFree(AiNodeGetLocalData(node));
}

shader_evaluate
{
   ColorState state = (ColorState) *((int*) AiNodeGetLocalData(node));
   AtLightSample ls;
   AiLightsGetSample(sg, ls);

   switch (state)
   {
   case CS_Li:
      sg->out.RGB() = ls.Li;
      break;
   case CS_Liu:
      sg->out.RGB() = ls.Liu;
      break;
   case CS_Lo:
      sg->out.RGB() = ls.Lo;
      break;
   default:
      sg->out.RGB() = AI_RGB_BLACK;
   }
}
