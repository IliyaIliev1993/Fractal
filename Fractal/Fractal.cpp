#include <iostream>
#include "MainApp.h"

int main()
{
    MainApp::GetInstance().Init();
    MainApp::GetInstance().Run();
    MainApp::GetInstance().DeInit();
}
