#include "prims.h"


void prims::Delete( void )
{
  for (int i = 0; i < NofElements; i++)
  {
    primitives[i]->Delete();  
    delete[] primitives[i];
  }
}

bool prims::FindStartLines( std::vector<int> &lineNo, const char *FileName )
{
  std::string tmp;
  static char Buf[1000];
  int N = 0;

  FILE *F;
  if ((F = fopen(FileName, "r")) == nullptr)
    return false;

  char oldc = ' ';
   
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ' && oldc != 'v')
      lineNo.push_back(N);
    N++;
    oldc = Buf[0];
  }
  lineNo.push_back(N - 1);

  fclose(F);
  return true;
}

bool prims::Load( const char *FileName )
{
  std::vector<int> lineNo;
  FindStartLines(lineNo, FileName);
  int sum = 0;
  
  for (int i = 0; i < size(lineNo) - 1; i++)
  {
    //primitives.push_back(pr);
    primitives[i] = new prim();
    primitives[i]->Load(FileName, lineNo[i], lineNo[i + 1], sum);
    sum += primitives[i]->NumOfV;
    NofElements++;
  }
  return true;
}
void prims::SetWorldTransormation( const dlgl::matr &MW )
{
  for (int i = 0; i < NofElements; i++)
    primitives[i]->SetWorldTransormation(MW);
  MatrWorld = MatrWorld * MW;
}



