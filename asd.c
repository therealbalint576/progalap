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
	int i=0,j=0;
    int water_range_h1=map.water_range,water_range_h2=map.water_range,water_range_l1=map.water_range,water_range_l2=map.water_range;
    if(current_y<map.water_range){
    	water_range_h1 = current_y;
	}
	if(map.height-current_y<map.water_range){
		water_range_h2 = map.height-current_y;
	}
    if(current_x<map.water_range){
    	water_range_l1 = current_x;
	}
	if(map.length-current_x<map.water_range){
		water_range_l2 = map.length-current_y;
	}
    current_y-=water_range_h1;
    current_x-=water_range_l1;
    int water_range_h = water_range_h1+water_range_h2;
    int water_range_l = water_range_l1+water_range_l2;
    for(i=current_y;i<=current_y+water_range_h;i++){
    	for(j=current_x;j<=current_x+water_range_l;j++){
    		if(j<map.length&&i<map.height&&i>-1&&j>-1){
				if(map.map[i][j] == '0'){
    			map.map[i][j] = '1';
				}
			}
		}
	}
    return map.map;
}

char** mountain_count(Maps map,int current_y,int current_x){
	int i=0,j=0;
    int mountain_range_h1=map.mountain_range,mountain_range_h2=map.mountain_range,mountain_range_l1=map.mountain_range,mountain_range_l2=map.mountain_range;
    if(current_y<map.mountain_range){
    	mountain_range_h1 = current_y;
	}
	if(map.height-current_y<map.mountain_range){
		mountain_range_h2 = map.height-current_y;
	}
    if(current_x<map.mountain_range){
    	mountain_range_l1 = current_x;
	}
	if(map.length-current_x<map.mountain_range){
		mountain_range_l2 = map.length-current_y;
	}
    current_y-=mountain_range_h1;
    current_x-=mountain_range_l1;
    int mountain_range_h = mountain_range_h1+mountain_range_h2;
    int mountain_range_l = mountain_range_l1+mountain_range_l2;
    for(i=current_y;i<=current_y+mountain_range_h;i++){
    	for(j=current_x;j<=current_x+mountain_range_l;j++){
    		if(j<map.length&&i<map.height&&i>-1&&j>-1){
    			if(map.map[i][j] == '0'){
    				map.map[i][j] = 'B';
				} else if(map.map[i][j] == '1' || map.map[i][j] == '~'){
					map.map[i][j] = '2';
				}
			}
		}
	}
    return map.map;
}

char** sandstorm_count(Maps map,int current_y,int current_x){
	int i=0,j=0;
    int sandstorm_range_h1=map.sandstorm_range,sandstorm_range_h2=map.sandstorm_range,sandstorm_range_l1=map.sandstorm_range,sandstorm_range_l2=map.sandstorm_range;
    if(current_y<map.sandstorm_range){
    	sandstorm_range_h1 = current_y;
	}
	if(map.height-current_y<map.sandstorm_range){
		sandstorm_range_h2 = map.height-current_y;
	}
    if(current_x<map.sandstorm_range){
    	sandstorm_range_l1 = current_x;
	}
	if(map.length-current_x<map.sandstorm_range){
		sandstorm_range_l2 = map.length-current_y;
	}
    current_y-=sandstorm_range_h1;
    current_x-=sandstorm_range_l1;
    int sandstorm_range_h = sandstorm_range_h1+sandstorm_range_h2;
    int sandstorm_range_l = sandstorm_range_l1+sandstorm_range_l2;
    for(i=current_y;i<=current_y+sandstorm_range_h;i++){
    	for(j=current_x;j<=current_x+sandstorm_range_l;j++){
    		if(j<map.length&&i<map.height&&i>-1&&j>-1){
    			map.map[i][j] = '0';
    		}
		}
	}
    return map.map;
}

int main() {
	int i=0,j=0;
    FILE *f_in;
    FILE *f_out;
    f_in = fopen("be.txt","r");
    f_out = fopen("ki.txt","w");

    Maps terrain;
    fscanf(f_in,"%d %d %d",&terrain.mountain_range,&terrain.water_range,&terrain.sandstorm_range);

    fscanf(f_in,"%d %d",&terrain.height,&terrain.length);
    terrain.map = (char**) malloc(terrain.height*sizeof(char*));
    for(i=0;i<terrain.length;i++){
        terrain.map[i] = (char*) malloc(terrain.length*sizeof(char));
    }
    char asd;
    for(i=0;i<terrain.height;i++){
        fscanf(f_in,"%c",&asd);
        for(j=0;j<terrain.length;j++){
            fscanf(f_in,"%c",&terrain.map[i][j]);
        }
    }
    
    for(i=0;i<terrain.height;i++){
        for(j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='~'){
                terrain.map = water_count(terrain,i,j);
            }
        }
    }
    for(i=0;i<terrain.height;i++){
        for(j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='A'){
                terrain.map = mountain_count(terrain,i,j);
            }
        }
    }
    for(i=0;i<terrain.height;i++){
        for(j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='X'){
                terrain.map = sandstorm_count(terrain,i,j);
            }
        }
    }

    int counter=0;
    for(i=0;i<terrain.height;i++){
        for(j=0;j<terrain.length;j++){
            if(terrain.map[i][j]=='2'){
                counter++;
            }
        }
    }
//90%-ban biztos vagyok benne hogy hibás a teszteset 4 meg 5 de idk
    fprintf(f_out,"%d\n",counter);
    for(i=0;i<terrain.length;i++){
        free(terrain.map[i]);
    }
    free(terrain.map);
    fclose(f_in);
    fclose(f_out);
    return 0;
}
