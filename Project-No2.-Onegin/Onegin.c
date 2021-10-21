#include"Onegin.h"

int main(int argc, char** argv){

	FILE *Onegin     = fopen(argv[1], "r");
	FILE *new_Onegin = fopen(argv[2], "w");

	assert(Onegin     != NULL);
	assert(new_Onegin != NULL);

	string_processing(onegin, new_Onegin, argv[3]);

    fclose(Onegin);
    fclose(new_Onegin);
}

void swap(line_t *lines, long left, long right){
	assert(lines);

	wchar_t *str_tmp   = lines[left]->line;
	lines[left]->line  = lines[right]->line;
	lines[right]->line = tmp;

	long len_tmp          = lines[left]->str_len;
	lines[left]->str_len  = lines[right]->str_len;
	lines[right]->str_len = len_tmp;
}

void string_processing(FILE *original, FILE *result, char *team){
	assert(original != NULL);
	assert(result   != NULL);
	assert(team     != NULL);

	fseek(original, 0, SEEK_END);
	long long file_length = ftell(original);
	
	wchar_t *buffer = (wchar_t *)calloc(file_length, sizoef(wchar_t));

	fseek(original, 0, SEEK_SET);

	int num_str = 0;
	file_lenght = 0;
	while(!feof(original)){

        buffer[file_lenght] = fgetwc(original);

        if(buffer[file_lenght] = '\n')
            num_str++;

        file_lenght++;        
	}

    free(buffer + file_lenght);
    
    struct line_t * lines = (line_t *)calloc(num_str, sizeof(wchar_t));
    assert(lines);    

    long p_ind   = 0;
    long str_ind = 0;

    while(True){

        while(True){

            if(p_ind >= file_lenght)
                break;            

            if((buffer[p_ind] == '\n') ||
               (buffer[p_ind] == '\t') ||
               (buffer[p_ind] == ' ')  ||
               (buffer[p_ind] == 'I')  ||
               (buffer[p_ind] == 'V')  ||
               (buffer[p_ind] == 'X')  ||
               (buffer[p_ind] == 'L')){
                p_ind++;
                break;
            }
            else break;
        }
        
        if(p_ind >= file_lenght)
            break;

        line[str_ind]->line    = &buffer[p_ind];
        line[str_ind]->str_len = p_ind;
            
        while(biffer[p_ind] != '\n'){
            if(p_ind >= file_lenght)
                break;

            p_ind++;
        }
        p_ind++;
            
        line[str_ind]->lenght = p_ind - line[str_ind]->lenght;
        str_ind++;
    }

    team_analysis(lines, str_ind, team);
    
    long i = 0,
         j = 0;

    while(i < str_ind){
        while(j < lines[i]->lenght){
            fprintf(result, "%lc", lines[i]->line[j]);
            j++;
        }
        i++;
    }
    
    free(buffer);
}

void team_analysis(line_t *lines, long str_ind, char *team){
    assert(lines);
    assert(team);
    
    int (*comparator)(line_t *, long, long);

    if(!srtcmp(team, "avfovit_sort"))
        comparator = avfovit_comparator; 
    else if(!strcmp(team, "rhyme_sort"))
         comparator = rhyme_comparator;
   
    long i = 0,
         j = 0;

    while(i < str_ind - 1){
        while(j < str_ind){
            if(comparator(lines, i, j) > 0)
                swap(lines, i, j);
            j = i + 1;
        }
        i++
    }
}
    
int avfovit_comparator(line_t *lines, long f_line, long s_line){
    assert(lines);

    long i = 0;
    long j = 0;

    while((lines[f_line].line[i] == '\'') || (!isalpha(lines[f_line].line[i])))
        i++; 
    while((lines[s_line].line[j] == '\'') || (!isalpha(lines[s_line].line[j])))
        j++;
    while((i < lines[f_line]->length) && (j < lines[s_line]->length)){
        if(lines[f_line]->line[i] == lines[s_line]->line[j]){
            i++;
            j++;
        }
        else
            return (lines[f_line]->line[i] - lines[s_line]->line[j]);
    }
    return (lines[f_line]->line[i] - lines[s_line]->line[j]);
}

int rhyme_comparator(line_t *lines, long f_line, long s_line){
     assert(lines);
 
     long i = lines[f_line]->lenght;
     long j = lines[s_line]->lenght;
 
     while((lines[f_line].line[i] == '\'') || (!isalpha(lines[f_line].line[i])))
         i--; 
     while((lines[s_line].line[j] == '\'') || (!isalpha(lines[s_line].line[j])))
         j--;
     while((i < lines[f_line]->length) && (j < lines[s_line]->length)){
         if(lines[f_line]->line[i] == lines[s_line]->line[j]){
             i--;
             j--;
         }
         else
             return -(lines[f_line]->line[i] - lines[s_line]->line[j]);
     }
     return -(lines[f_line]->line[i] - lines[s_line]->line[j]);
 }
