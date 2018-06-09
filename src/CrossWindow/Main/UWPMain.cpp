#include "../Common/Init.h"
#include "Main.h"

#include <comdef.h>
#include <vector>

[Platform::MTAThread]
int WINAPIV main(Platform::Array<Platform::String^>^ params)
{
  // Downgrade to c style main function:
  std::vector<const char*> args;

  for (Platform::String^& s : params)
  {
    wchar_t* w = s->Data;
    _bstr_t b(w);
    args.emplace_back((const char*)b);
  }

  xwin::init(params);
  xmain(args.size(), (const char**)args.data());
	return 0;
}
