#ifndef CLEARSCREEN_HPP_
#define CLEARSCREEN_HPP_

#include<windows.h>
#include <unistd.h>

//uses windows.h to clear screen
void ClearScreen (void)
{
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  //Get the number of cells in the current buffer
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  //Fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ', cellCount, homeCoords, &count))
	  return;

  //Fill the entire buffer with the current colors and attributes
  if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
	  return;

  //Move the cursor home
  SetConsoleCursorPosition( hStdOut, homeCoords );
}

//uses term.h to clear screen
//void Clearscreen()
//{
//  if (!cur_term)
//    {
//    int result;
//    setupterm(NULL, STDOUT_FILENO, &result);
//    if (result <= 0) return;
//    }
//
//  putp(tigetstr("clear"));
//}

//flushes screen with endlines to clear the console
void ClearScreen (std::size_t n = 10)
{
	for(std::size_t i{}; i < n; ++i)
		std::cout<<std::string(100, '\n');
}


#endif
