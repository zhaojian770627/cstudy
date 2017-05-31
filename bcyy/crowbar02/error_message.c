#include <string.h>
#include "crowbar.h"

MessageFormat crb_compile_error_message_format[]={
  {"dummy"},
  {"has grammar error near ($(token))"},
  {"error char ($(bad_char))."},
  {"function name repeated."},
  {"dummy"}
};

MessageFormat crb_runtime_error_message_format[]={
  {"dummy"},
  {"foundn't varible($(name))"},
  {"foundn't function($(name))"},
  {"input args more than function definition args."},
  {"inout args less than function definition args."},
  {"condition expr must be boolean."},
  {"sub operate data must num type."},
  {"binary operator $(operator) data type error."},
  {"$(operator) can't use in boolean type."},
  {"please input path and open type for fopen.both and string thpe."},
  {"please input file pointer for fclose."},
  {"please input file pointer for fgets."},
  {"please input file pointer for fputs."},
  {"null must used in == and != (can't used in $(operator)"},
  {"can't div by 0"},
  {"global variable $(name) not exists."},
  {"can't use global statement outside function."},
  {"operator $(operator) can't useed in string type."},
  {"dummy"}
};
