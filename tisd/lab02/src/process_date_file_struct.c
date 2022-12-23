/* This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#include "../inc/process_date_file_struct.h"

char delete_struct_by_firstname(subscribers_t *subscribers, size_t *count_structs, char *name, char *filename, size_t *delete_structs)
{
	char rc = ERR_OK;
	for(size_t i = 0; i < (*count_structs) && rc == ERR_OK;)
	{
		if(strcmp(name, (subscribers+i)->firstname) == 0)
		{
			delete_subscribers_from_array(subscribers, count_structs, i);
			++(*delete_structs);
		}
		else
		{
			rc = write_struct_to_file("tmp.txt", (subscribers+i));
			++i;
		}
	}
	if(rc == ERR_OK && *(delete_structs) != 0)
		rename("tmp.txt", filename);
	return rc;
}

void delete_subscribers_from_array(subscribers_t *subscribers, size_t *count_structs, size_t index)
{
	for(size_t i = index; i < (*count_structs) - 1; ++i)
	{
		*(subscribers+i) = *(subscribers+i+1);
	}
	--(*count_structs);
}




char write_struct_to_file(char *filename, subscribers_t *subscribers)
{
	char rc = ERR_OK;
	FILE *f = fopen(filename, "a");
	if(f != NULL)
	{
		if(subscribers->status == offical)
			fprintf(f, "%s\n%s\n%s\n%s\nO\n%s\n%s\n", subscribers->firstname, subscribers->lastname, subscribers->phone_number,
				subscribers->adress, (subscribers->variate_status).offical.job_title, (subscribers->variate_status).offical.organization);
		else
			fprintf(f, "%s\n%s\n%s\n%s\nP\n%d.%d.%d\n", subscribers->firstname, subscribers->lastname, subscribers->phone_number,
				subscribers->adress, (subscribers->variate_status).private.date_birth.day, (subscribers->variate_status).private.date_birth.month, (subscribers->variate_status).private.date_birth.year);
		fclose(f);
	}
	else
	{
		rc = ERR_OPEN_FILE;
	}
	return rc;
}


char read_all_structs_from_file(char *file_name, subscribers_t **subscribers, size_t *count_structs, size_t *start_count_struct)
{
	char rc = ERR_OK;
	FILE *f = fopen(file_name, "r");
	if(f == NULL)
	{
		rc = ERR_OPEN_FILE;
	}
	else
	{
		short int is_stdin_input = 0;
		rc = read_struct_from_file(f, *subscribers, count_structs, is_stdin_input);
		while(rc == ERR_OK)
		{
			if(*count_structs == *start_count_struct)
			{
				rc = realloc_mem(subscribers, start_count_struct);
			}
			if(rc == ERR_OK)
			{
				rc = read_struct_from_file(f, (*subscribers)+(*count_structs), count_structs, is_stdin_input);
			}
		}
		if(rc == ERR_OK_EOF && *count_structs == 0)
			rc = ERR_EMPTY_FILE;
		else if(rc == ERR_OK_EOF && *count_structs > 0)
			rc = ERR_OK;
		fclose(f);

	}
	return rc;
}

char add_struct(subscribers_t **subscribers, size_t *count_structs, size_t *start_count_struct)
{
	char rc = ERR_OK;
	if(*count_structs == *start_count_struct)
	{
		realloc_mem(subscribers, start_count_struct);
	}
	short int is_stdin_input = 1;
	clean_stdin();
	rc = read_struct_from_file(stdin, (*subscribers)+(*count_structs), count_structs, is_stdin_input);
	return rc;
}



char realloc_mem(subscribers_t **subscribers, size_t *start_count_struct)
{
	char rc = ERR_OK;
	*start_count_struct = (*start_count_struct) * 2;
	subscribers_t *pbuf = realloc(*subscribers, *start_count_struct * sizeof(subscribers_t));
	if(pbuf != NULL)
	{
		(*subscribers) = pbuf;
	}
	else
	{
		rc = ERR_ALLOCATE_MEM;
	}
	return rc;
}


char read_struct_from_file(FILE *f, subscribers_t *subscribers, size_t *count_structs, short int is_stdin_input)
{
	char rc = ERR_OK;
	if(f == NULL)
	{
		rc = ERR_OPEN_FILE;
	}
	else
	{
		if(is_stdin_input)
		{
			printf("Введите фамилию(макс. 20 символов): ");
		}
		rc = read_str_to_buf(f, subscribers->firstname, MAX_FIRSTNAME_LEN);
		if(rc == ERR_OK)
		{
			if(!is_name_correct(subscribers->firstname))
			{
				rc = ERR_INCORRECT_NAME;
			}
		}
		else if(rc == ERR_EOF)
		{
			rc = ERR_OK_EOF;
		}

		if(rc == ERR_OK)
		{
			if(is_stdin_input)
			{
				printf("Введите имя(макс. 20 символов): ");
			}			
			rc = read_str_to_buf(f, subscribers->lastname, MAX_LASTNAME_LEN);
			if(rc == ERR_OK)
			{
				if(!is_name_correct(subscribers->lastname))
				{
					rc = ERR_INCORRECT_NAME;
				}
			}
		}

		if(rc == ERR_OK)
		{
			if(is_stdin_input)
			{
				printf("Введите телефонный номер(в формате - 10 цифр номера, без кода страны): ");
			}	
			rc = read_str_to_buf(f, subscribers->phone_number, LEN_PHONE_NUMBER);
			if(rc == ERR_OK)
			{
				rc = (is_num(subscribers->phone_number) && strlen(subscribers->phone_number) == LEN_PHONE_NUMBER_CORRECT) ? ERR_OK : ERR_PHONE_NUMBER;
			}
		}

		if(rc == ERR_OK)
		{
			if(is_stdin_input)
			{
				printf("Введите адрес(макс. 60 символов): ");
			}	
			rc = read_str_to_buf(f, subscribers->adress, MAX_LEN_ADRESS);
		}
		if(rc == ERR_OK)
		{
			char buf[LEN_BUF_STATUS];
			if(is_stdin_input)
			{
				printf("Введите статус(P - личный, O - служебный): ");
			}	
			rc = read_str_to_buf(f, buf, LEN_BUF_STATUS);
			if(rc == ERR_OK)
			{
				if(strlen(buf) == 1 && !strcmp(buf, "P"))
				{
					subscribers->status = private;
				}
				else if(strlen(buf) == 1 && !strcmp(buf, "O"))
				{
					subscribers->status = offical;
				}
				else
				{
					rc = ERR_STATUS;
				}
			}
		}
		if(rc == ERR_OK)
		{
			if(subscribers->status == offical)
			{
				if(is_stdin_input)
				{
					printf("Введите должность(макс. 20 символов): ");
				}	
				rc = read_str_to_buf(f, (subscribers->variate_status).offical.job_title, MAX_LEN_JOB_TITLE);
				if(rc == ERR_OK)
				{
					if(is_stdin_input)
					{
						printf("Введите название организации(макс. 35 символов): ");
					}	
					rc = read_str_to_buf(f, (subscribers->variate_status).offical.organization, MAX_LEN_ORGANIZATION);
				}
			}
			else
			{
				char buf[MAX_LEN_DATE] = { 0 };
				if(is_stdin_input)
				{
					printf("Введите дату(dd.mm.yyyy): ");
				}	
				rc = read_str_to_buf(f, buf, MAX_LEN_DATE);
				if(rc == ERR_OK)
				{
					rc = process_date(buf, subscribers);
				}
			}
		}
		if(rc == ERR_OK)
			++(*count_structs);
	}

	return rc;
}


char read_str_to_buf(FILE *f, char *buf, size_t max_len)
{
	char rc = ERR_OK;
    if (fgets(buf, max_len+1, f) == NULL)
    {
    	if (feof(f) == 0)
            rc = ERR_READ_FILE;
        else
            rc = ERR_EOF;
    }
    else
    {
    	if((buf)[strlen(buf) - 1] != '\n')
    	{
    		if(strlen(buf)==max_len)
    		{
    			rc = ERR_STR_TOO_LONG;
    		}
    	}
    	else if (!((buf)[strlen(buf) - 1] = 0) && strlen(buf) == 0)
    	{
    		rc = ERR_EMPTY_STR;
    	}

    }
    return rc;
}


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}