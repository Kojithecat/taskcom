#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h>

int main(int argc, char* argv[]){
    

    printf("Hello worl");	
    FILE *fp = fopen("tasks.json", "r");
    if(fp == NULL){
    	printf("Error: Unable to open the file.\n");
	return 1;
    }
    
    printf("Hello worl");	
    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);
    cJSON *json = cJSON_Parse(buffer);
    if(json = NULL){
    	const char *error_ptr  = cJSON_GetErrorPtr();
    	if(error_ptr != NULL){
    	    printf("Error %s\n", error_ptr);
    	}
    }

    if(argc == 3 && !strcmp(argv[1], "task")){
	printf("Hello worl");
	char* task = argv[2];	
	//strcpy(task, argv[2]);
	printf("%s", task);	
	cJSON_AddStringToObject(json, "task", task);	
	char *json_str = cJSON_Print(json);
	fp = fopen("tasks.json", "w");
	if(fp == NULL){
            printf("Error: Unable to open the file.\n");
	    return 1;
        }
	printf("%s",json_str);
	//fputs(json_str, fp);
	fclose(fp);
	//cJSON_free(json_str);
	cJSON_Delete(json);
    }
 
    return 0;

}
