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
    int water_range_h=map.water_range,water_range_l=map.water_range;
    if(current_y<map.water_range || map.height-current_y < map.water_range){
        if(current_y<map.height/2){
            water_range_h = current_y;
        } else {
            water_range_h = map.height-current_y;
        }
    }
    if(current_x<map.water_range || map.length-current_x < map.water_range){
        if(current_x<map.length/2){
            water_range_l = current_x;
        } else {
            water_range_l = map.height-current_x;
        }
    }
    current_y-=water_range_h;
    current_x-=water_range_l;
    printf("ez a current_y: %d\n ez a current x: %d\n",current_y,current_x);
    for(int i=current_y;i<water_range_h*2+1;i++){
        for(int j=current_x;j<water_range_l*2+1;j++){
            if(map.map[i][j]=='0'){
                map.map[i][j]='1';
            }
        }
    }
    for(int i=0;i<map.height;i++){
        for(int j=0;j<map.length;j++){
            printf("%c",map.map[i][j]);
        }
        printf("\n");
    }
    return map.map;
}
//--------------------------------------
char** mountain_count(Maps map,int current_y,int current_x){
    int mountain_range_h=map.mountain_range,mountain_range_l=map.mountain_range;
    if(current_y<map.mountain_range || map.height-current_y < map.mountain_range){
        if(current_y>map.height/2){
            mountain_range_h = map.height-current_y;
        } else {
            mountain_range_h = current_y;
        }
    }
    if(current_x<map.mountain_range || map.length-current_x < map.mountain_range){
        if(current_x>map.length/2){
            mountain_range_l = map.length-current_x;
        } else {
            mountain_range_l = current_x;
        }
    }
    current_y-=mountain_range_h;
    current_x-=mountain_range_l;
    printf("ez a mountain_range_h: %d\n ez a mountain_range_l: %d\n",mountain_range_h,mountain_range_l);
    for(int i=current_y;i<mountain_range_h*2+1;i++){
        for(int j=current_x;j<mountain_range_l*2+1;j++){
            if(map.map[i][j]=='0'){
                map.map[i][j] = '1';
            } else if(map.map[i][j]=='~' || map.map[i][j]=='1' ){
                map.map[i][j] = '2';
            }
        }
    }
    for(int i=0;i<map.height;i++){
        for(int j=0;j<map.length;j++){
            printf("%c",map.map[i][j]);
        }
        printf("\n");
    }
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
    char asd;
    for(int i=0;i<terrain.height;i++){
        fscanf(f_in,"%c",&asd);
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
    printf("\n");
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='X'){
                terrain.map = sandstorm_count(terrain,i,j);
            }
        }
    }
    printf("\n");
    for(int i=0;i<terrain.height;i++){
        for(int j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='A'){
                terrain.map = mountain_count(terrain,i,j);
            }
        }
    }
    printf("\n");
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
            if(terrain.map[i][j]=='2'){
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