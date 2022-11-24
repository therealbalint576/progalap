#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char** map;
    int mountain_range;
    int water_range;
    int sandstorm_range;
    int height;
    int length;
}Maps;

char** water_count(Maps map,int current_y,int current_x){
    current_y-=map.water_range;
    current_x-=map.water_range;
    current_x++;
    current_y--;
    printf("ez a current_y: %d\n ez a current_x: %d\n",current_y,current_x);
    for(int i=current_y;i<map.water_range*2+1;i++){
        for(int j=current_x;j<map.water_range*2+1;j++){
            printf("itt vagyunk epp: map[%d][%d]\n ez van itt: %c\n",i,j,map.map[i][j]);
            if(map.map[i][j]=='0'){
                map.map[i][j]='1';
                printf("ez lett itt: %c\n",map.map[i][j]);
            }
        }
    }
    return map.map;
}
//--------------------------------------
char** mountain_count(Maps map,int current_y,int current_x){

    return map.map;
}
//--------------------------------------
char** sandstorm_count(Maps map,int current_y,int current_x){

    return map.map;
}
//--------------------------------------
int main() {
    FILE *f_in;
    FILE *f_out;
    f_in = fopen("be.txt","r");
    f_out = fopen("ki.txt","w");
//--------------------------------------
    Maps terrain;
    fscanf(f_in,"%d %d %d",&terrain.mountain_range,&terrain.water_range,&terrain.sandstorm_range);
//--------------------------------------
    fscanf(f_in,"%d %d",&terrain.height,&terrain.length);
    terrain.map = (char**) malloc(terrain.height*sizeof(char*));
    for(int i=0;i<terrain.length;i++){
        terrain.map[i] = (char*) malloc(terrain.length*sizeof(char));
    }
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            fscanf(f_in,"%c",&terrain.map[i][j]);
        }
    }
//--------------------------------------
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='~'){
                terrain.map = water_count(terrain,i,j);
            }
        }
    }
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='A'){
                terrain.map = mountain_count(terrain,i,j);
            }
        }
    }
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='X'){
                terrain.map = sandstorm_count(terrain,i,j);
            }
        }
    }
//--------------------------------------
    int counter=0;
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='1'){
                counter++;
            }
        }
    }
//--------------------------------------
    fprintf(f_out,"%d\n",counter);
    for(int i=0;i<terrain.length;i++){
        free(terrain.map[i]);
    }
    free(terrain.map);
    fclose(f_in);
    fclose(f_out);
    return 0;
}