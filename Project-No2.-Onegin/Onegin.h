#include<stdio.h>
#include<wchar.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<assert.h>
#include<stddef.h>
#include<stdlib.h>

const int limit_size = 512;
const int col_size = 1024;

struct line_t{
    wchar_t *line;
    long str_len;
};

//=============================================================================
///    \brief String Processing
///    \author Kolyadich Mark
///    \param [in] original - source file for processing
///    \param [in] result   - the file where the processing result will be written
///    \param [in] team     - mode of how to process the dat
///    \version 1.0
///    \date 23.10.2021
//=============================================================================
void string_processing(FILE *original, FILE *result, char *team);

//=============================================================================
///    \brief Full Sorting strings
///    \author Kolyadich Mark
///    \param [in] original - source file for Sorting
///    \param [in] result   - the file where the processing result will be written
///    \param [in] team     - command for text conversion method
///    \version 1.0
///    \date 23.10.2021
//=============================================================================
void team_analysis(line_t *lines, long str_ind, char *team);

//=============================================================================
///    \brief  Sorting strings for avfovit
///    \author Kolyadich Mark
///    \param [in] original - source file for Sorting
///    \param [in] f_line   - first line
///    \param [in] s_line1  - second line
///    \version 1.0
///    \date 23.10.2021
//============================================================================= 
int avfovit_comparator(line_t *lines, long f_line, long s_line);

//=============================================================================
///    \brief  Sorting strings for rhyme
///    \author Kolyadich Mark
///    \param [in] original - source file for Sorting
///    \param [in] f_line   - first line
///    \param [in] s_line1  - second line
///    \version 1.0
///    \date 23.10.2021
//============================================================================= 
int rhyme_comparator(line_t *lines, long f_line, long s_line);

//=============================================================================
///    \brief Swap two string structures
///    \author Kolyadich Mark
///    \param [in] lines - pointer to an array of string structures
///    \param [in] left  - first line number
///    \param [in] right - second line number
///    \version 1.0
///    \date 23.10.2021
//==============================================================================
void swap(line_t *lines, long left, long right);
