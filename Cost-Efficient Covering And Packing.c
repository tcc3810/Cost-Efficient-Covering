#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxterm 50
#define SWAP(a , b) {int tmp = a; a = b; b = tmp;}
int controler = 15;

int bits_num;
int switches_num;
int links_num;
int rule_num;
int square;

int order[Maxterm][Maxterm];
int distance[Maxterm];
int check[Maxterm];
int path[Maxterm];

int choose(int num){
	int min = 100000;
	int min_pos = -1;
	for(int i = 0 ; i < num ; i++){
		if(check[i] == 0 && distance[i] < min){
			min = distance[i];
			min_pos = i;
		}
	}
	return min_pos;
}

void Dijkstra(int start , int num){ //start = 0
	//初始化
	for(int i = 0 ; i < num ; i++){
		check[i] = 0;
		path[i] = -1;
		distance[i] = order[start][i];
	}
	//start更新
	check[start] = 1;
	path[start] = -1;
	distance[start] = 0;
	for(int i = 0 ; i < num ; i++){
		if(distance[i] < 100000 && distance[i] > 0)
			path[i] = start;
	}
	for(int i = 0 ; i < num - 2 ; i++){
		int u = choose(num);
		check[u] = 1;
		for(int w = num - 1 ; w >= 0 ; w--){
			if(check[w] == 0 && distance[u] + order[u][w] < distance[w]){
				distance[w] = order[u][w] + distance[u];
				path[w] = u; // 如果距離不一樣,選最小id的
			}
			else if(check[w] == 0 && distance[u] + order[u][w] == distance[w]){
				// 如果距離一樣,找節點數最少的
				int w_cnt = 0; // 到w的節點數
				int u_cnt = 0; // 到u的節點數
				int w_id = w;
				int u_id = u;
				while(w_id != -1){
					w_id = path[w_id];
					w_cnt++;
				}
				while(u_id != -1){
					u_id = path[u_id];
					u_cnt++;
				}
				if(w_cnt < u_cnt + 1)
					path[w] = path[w];
				else if(w_cnt > u_cnt + 1)
					path[w] = u;
				else if(w_cnt == u_cnt + 1){
					w_id = w;
					u_id = u;
					if(w_id < u_id)
						path[w] = path[w];
					else if(w_id > u_id)
						path[w] = u;
				}
			}
		}
	}
}
// 1. MapUtility	每次調查完所有的utility, 找到最大就free掉整個LinkedList。
// 2. MapRule		把所有的規則LinkedList在一起, 永不free。
struct LinkedList{
	int index;
	double utility;
	long long int belongs;
	long long int part;
	int all_cover_num;
	char condition[20];

	int src_left;
	int src_right;
	int dst_left;
	int dst_right;

	struct LinkedList *next;
};
struct SwitchRule{
	int index;
	int capacity;
	struct SwitchList *List;
};
struct SwitchList{
	char condition[20];
	char src[20];
	char dst[20];
	struct SwitchList *next;
};
struct LinkedList *insert_MapRule(struct LinkedList *MapRule , char *word1 , char *word2 , char *word3 , int index , int bits){
	struct LinkedList *R = malloc(sizeof(struct LinkedList));
	if(bits == 2){
		// 找src
		if(strcmp(word1 , "00") == 0){
			R->src_left = 1;
			R->src_right = 1;
		}
		else if(strcmp(word1 , "01") == 0){
			R->src_left = 2;	
			R->src_right = 2;
		}
		else if(strcmp(word1 , "10") == 0){
			R->src_left = 3;
			R->src_right = 3;
		}
		else if(strcmp(word1 , "11") == 0){
			R->src_left = 4;
			R->src_right = 4;
		}
		else if(strcmp(word1 , "0*") == 0){
			R->src_left = 1;
			R->src_right = 2;
		}
		else if(strcmp(word1 , "1*") == 0){
			R->src_left = 3;
			R->src_right = 4;
		}
		else if(strcmp(word1 , "*") == 0){
			R->src_left = 1;	
			R->src_right = 4;
		}
		// 找dst	
		if(strcmp(word2 , "00") == 0){
			R->dst_left = 1;
			R->dst_right = 1;
		}
		else if(strcmp(word2 , "01") == 0){
			R->dst_left = 2;	
			R->dst_right = 2;
		}
		else if(strcmp(word2 , "10") == 0){
			R->dst_left = 3;
			R->dst_right = 3;
		}
		else if(strcmp(word2 , "11") == 0){
			R->dst_left = 4;
			R->dst_right = 4;
		}
		else if(strcmp(word2 , "0*") == 0){
			R->dst_left = 1;
			R->dst_right = 2;
		}
		else if(strcmp(word2 , "1*") == 0){
			R->dst_left = 3;
			R->dst_right = 4;
		}
		else if(strcmp(word2 , "*") == 0){
			R->dst_left = 1;	
			R->dst_right = 4;
		}
	}
	else if(bits == 3){
		// 找src
		if(strcmp(word1 , "000") == 0){
			R->src_left = 1;
			R->src_right = 1;
		}
		else if(strcmp(word1 , "001") == 0){
			R->src_left = 2;	
			R->src_right = 2;
		}
		else if(strcmp(word1 , "010") == 0){
			R->src_left = 3;
			R->src_right = 3;
		}
		else if(strcmp(word1 , "011") == 0){
			R->src_left = 4;
			R->src_right = 4;
		}
		else if(strcmp(word1 , "100") == 0){
			R->src_left = 5;
			R->src_right = 5;
		}
		else if(strcmp(word1 , "101") == 0){
			R->src_left = 6;
			R->src_right = 6;
		}
		else if(strcmp(word1 , "110") == 0){
			R->src_left = 7;
			R->src_right = 7;
		}
		else if(strcmp(word1 , "111") == 0){
			R->src_left = 8;
			R->src_right = 8;
		}
		else if(strcmp(word1 , "00*") == 0){
			R->src_left = 1;
			R->src_right = 2;
		}
		else if(strcmp(word1 , "01*") == 0){
			R->src_left = 3;
			R->src_right = 4;
		}
		else if(strcmp(word1 , "10*") == 0){
			R->src_left = 5;
			R->src_right = 6;
		}
		else if(strcmp(word1 , "11*") == 0){
			R->src_left = 7;
			R->src_right = 8;
		}
		else if(strcmp(word1 , "0*") == 0){
			R->src_left = 1;	
			R->src_right = 4;
		}
		else if(strcmp(word1 , "1*") == 0){
			R->src_left = 5;	
			R->src_right = 8;
		}
		else if(strcmp(word1 , "*") == 0){
			R->src_left = 1;	
			R->src_right = 8;
		}
		// 找dst	
		if(strcmp(word2 , "000") == 0){
			R->dst_left = 1;
			R->dst_right = 1;
		}
		else if(strcmp(word2 , "001") == 0){
			R->dst_left = 2;	
			R->dst_right = 2;
		}
		else if(strcmp(word2 , "010") == 0){
			R->dst_left = 3;
			R->dst_right = 3;
		}
		else if(strcmp(word2 , "011") == 0){
			R->dst_left = 4;
			R->dst_right = 4;
		}
		else if(strcmp(word2 , "100") == 0){
			R->dst_left = 5;
			R->dst_right = 5;
		}
		else if(strcmp(word2 , "101") == 0){
			R->dst_left = 6;
			R->dst_right = 6;
		}
		else if(strcmp(word2 , "110") == 0){
			R->dst_left = 7;
			R->dst_right = 7;
		}
		else if(strcmp(word2 , "111") == 0){
			R->dst_left = 8;
			R->dst_right = 8;
		}
		else if(strcmp(word2 , "00*") == 0){
			R->dst_left = 1;
			R->dst_right = 2;
		}
		else if(strcmp(word2 , "01*") == 0){
			R->dst_left = 3;
			R->dst_right = 4;
		}
		else if(strcmp(word2 , "10*") == 0){
			R->dst_left = 5;
			R->dst_right = 6;
		}
		else if(strcmp(word2 , "11*") == 0){
			R->dst_left = 7;
			R->dst_right = 8;
		}
		else if(strcmp(word2 , "0*") == 0){
			R->dst_left = 1;	
			R->dst_right = 4;
		}
		else if(strcmp(word2 , "1*") == 0){
			R->dst_left = 5;	
			R->dst_right = 8;
		}
		else if(strcmp(word2 , "*") == 0){
			R->dst_left = 1;	
			R->dst_right = 8;
		}
	}
	// 找condition	
	if(strcmp(word3 , "Permit") == 0){
		strcpy(R->condition , "Permit");
	}
	else if(strcmp(word3 , "Drop") == 0){
		strcpy(R->condition , "Drop");
	}
	else if(strcmp(word3 , "Fwd") == 0){
		strcpy(R->condition , "Fwd");
	}
		
	R->index = index + 15;
	long long int belongs = 1;
	for(int i = 0 ; i < R->index ; i++)
		belongs *= 2;
	R->belongs = belongs;
	if(MapRule == NULL){
		return R;
	}
	struct LinkedList *pre , *p = MapRule;
	while(p){
		pre = p;
		p = p->next;
	}
	pre->next = R;
	return MapRule;
}

struct LinkedList *insert_utility(struct LinkedList *MapRule, struct LinkedList *MapUtility, int src_left, int src_right, int dst_left, int dst_right , int size){
	int all_cover = 0;	// 覆蓋整個Rule
	int part_cover = 0;	// 覆蓋部份Rule
	long long int belongs = 0;
	long long int part = 0;
	
	int mark[square][square];
	for(int i = 0 ; i < square ; i++)
		for(int j = 0 ; j < square ; j++)
			mark[i][j] = 0;
	
	struct LinkedList *R = MapRule;
	while(R){
		int mark_rule[square][square];
		for(int i = 0 ; i < square ; i++)
			for(int j = 0 ; j < square ; j++)
				mark_rule[i][j] = 0;
		for(int src = R->src_left - 1 ; src < R->src_right ; src++){
			for(int dst = R->dst_left - 1 ; dst < R->dst_right ; dst++){
				mark_rule[src][dst] = 1;
			}
		}

		int cnt = 0;
		int part_cnt = 0;
		for(int src = src_left - 1 ; src < src_right ; src++){
			for(int dst = dst_left - 1 ; dst < dst_right ; dst++){
				if(mark_rule[src][dst] == 1 && mark[src][dst] == 0){
					cnt++;
					mark[src][dst] = 1;
				}
				else if(mark_rule[src][dst] == 1 && mark[src][dst] == 1){
					part_cnt++;
				}
			}
		}
		if(cnt > 0 && (cnt + part_cnt) == (R->src_right - R->src_left + 1) * (R->dst_right - R->dst_left + 1)){
			all_cover++;
			long long int tmp = 1;
			for(int i = 0 ; i < R->index ; i++)
				tmp *= 2;
			belongs += tmp;
		}
		else if(cnt > 0){
			part_cover++;

			long long int tmp = 1;
			for(int i = 0 ; i < R->index ; i++)
				tmp *= 2;
			part += tmp;

		}
		R = R->next;
	}

	struct LinkedList *U = malloc(sizeof(struct LinkedList));
	U->utility = (double)(all_cover - 1) / (part_cover + 1);
	U->all_cover_num = all_cover;
	U->belongs = belongs;
	U->part = part;
	U->src_left = src_left;
	U->src_right = src_right; 
	U->dst_left = dst_left;
	U->dst_right = dst_right;
	U->next = NULL;

	if(all_cover + part_cover > size || U->utility <= 0){
		return MapUtility;
	}
	else if(MapUtility == NULL){
		return U;
	}
	//規則一：utility 取最大
	else if(MapUtility->utility < U->utility){
		return U;
	}
	else if(MapUtility->utility > U->utility){
		return MapUtility;
	}
	//規則二：包最多的all_cover
	else if(MapUtility->all_cover_num < U->all_cover_num){
		return U;
	}
	else if(MapUtility->all_cover_num > U->all_cover_num){
		return MapUtility;
	}
	//規則三：有最小的size
	else if((MapUtility->src_right - MapUtility->src_left + 1) * (MapUtility->dst_right - MapUtility->dst_left + 1) > (U->src_right - U->src_left + 1) * (U->dst_right - U->dst_left + 1)){
		return U;
	}
	else if((MapUtility->src_right - MapUtility->src_left + 1) * (MapUtility->dst_right - MapUtility->dst_left + 1) < (U->src_right - U->src_left + 1) * (U->dst_right - U->dst_left + 1)){
		return MapUtility;
	}
	
	//規則四：最小的all_cover -> belongs
	long long int x = MapUtility->belongs;
	long long int y = U->belongs;
	while(x % 2 == y % 2){
		if(x == 0 && y == 0)
			break;
		x = x / 2;
	       	y = y / 2;
	}
	if(x % 2 < y % 2)
		return U;
	
	return MapUtility;
}

struct LinkedList *struct_utility(struct LinkedList *MapRule , struct LinkedList *MapUtility , int size){ // 調查所有的utility
	for (int src_unit = 1 ; src_unit <= square ; src_unit *= 2){
		for(int src_id = 1 ; src_id + src_unit - 1 <= square ; src_id += src_unit){
			int src_left = src_id;
			int src_right = src_id + src_unit - 1;
			for (int dst_unit = 1 ; dst_unit <= square ; dst_unit *= 2){
				for(int dst_id = 1 ; dst_id + dst_unit - 1 <= square ; dst_id += dst_unit){
					int dst_left = dst_id;
					int dst_right = dst_id + dst_unit - 1;
					MapUtility = insert_utility(MapRule , MapUtility , src_left , src_right , dst_left , dst_right , size);
				}
			}
		}
	}
	return MapUtility;
}

struct LinkedList *insert_NewMapRule(struct LinkedList *MapRule , struct LinkedList *MapUtility){
	if(MapUtility == NULL)
		return MapRule;
	struct LinkedList *R = malloc(sizeof(struct LinkedList));
	
	long long int belongs = MapUtility->belongs;
	long long int tmp = 1;
	for(int i = 0 ; i < controler ; i++)
		tmp *= 2;
	belongs += tmp;
	controler--;
	
	R->index = controler + 1;
	R->all_cover_num = MapUtility->all_cover_num;
	R->belongs = belongs;
	R->part = MapUtility->part;
	R->src_left = MapUtility->src_left;
	R->src_right = MapUtility->src_right;
	R->dst_left = MapUtility->dst_left;
	R->dst_right = MapUtility->dst_right;
	strcpy(R->condition , "Fwd");
	R->next = MapRule;
	return R;
}
void transmation(int bits , struct LinkedList *L , char *src , char *dst){
	if(bits == 2){
		if(L->src_left == 1 && L->src_right == 1)
			strcpy(src , "00");
		else if(L->src_left == 2 && L->src_right == 2)
			strcpy(src , "01");
		else if(L->src_left == 3 && L->src_right == 3)
			strcpy(src , "10");
		else if(L->src_left == 4 && L->src_right == 4)
			strcpy(src , "11");
		else if(L->src_left == 1 && L->src_right == 2)
			strcpy(src , "0*");
		else if(L->src_left == 3 && L->src_right == 4)
			strcpy(src , "1*");
		else
			strcpy(src , "*");
	
		if(L->dst_left == 1 && L->dst_right == 1)
			strcpy(dst , "00");
		else if(L->dst_left == 2 && L->dst_right == 2)
			strcpy(dst , "01");
		else if(L->dst_left == 3 && L->dst_right == 3)
			strcpy(dst , "10");
		else if(L->dst_left == 4 && L->dst_right == 4)
			strcpy(dst , "11");
		else if(L->dst_left == 1 && L->dst_right == 2)
			strcpy(dst , "0*");
		else if(L->dst_left == 3 && L->dst_right == 4)
			strcpy(dst , "1*");
		else
			strcpy(dst , "*");
		}
	else if(bits == 3){
		if(L->src_left == 1 && L->src_right == 1)
			strcpy(src , "000");
		else if(L->src_left == 2 && L->src_right == 2)
			strcpy(src , "001");
		else if(L->src_left == 3 && L->src_right == 3)
			strcpy(src , "010");
		else if(L->src_left == 4 && L->src_right == 4)
			strcpy(src , "011");
		else if(L->src_left == 5 && L->src_right == 5)
			strcpy(src , "100");
		else if(L->src_left == 6 && L->src_right == 6)
			strcpy(src , "101");
		else if(L->src_left == 7 && L->src_right == 7)
			strcpy(src , "110");
		else if(L->src_left == 8 && L->src_right == 8)
			strcpy(src , "111");
			
		else if(L->src_left == 1 && L->src_right == 2)
			strcpy(src , "00*");
		else if(L->src_left == 3 && L->src_right == 4)
			strcpy(src , "01*");
		else if(L->src_left == 5 && L->src_right == 6)
			strcpy(src , "10*");
		else if(L->src_left == 7 && L->src_right == 8)
			strcpy(src , "11*");
		else if(L->src_left == 1 && L->src_right == 4)
			strcpy(src , "0*");
		else if(L->src_left == 5 && L->src_right == 8)
			strcpy(src , "1*");
		else
			strcpy(src , "*");

		if(L->dst_left == 1 && L->dst_right == 1)
			strcpy(dst , "000");
		else if(L->dst_left == 2 && L->dst_right == 2)
			strcpy(dst , "001");
		else if(L->dst_left == 3 && L->dst_right == 3)
			strcpy(dst , "010");
		else if(L->dst_left == 4 && L->dst_right == 4)
			strcpy(dst , "011");
		else if(L->dst_left == 5 && L->dst_right == 5)
			strcpy(dst , "100");
		else if(L->dst_left == 6 && L->dst_right == 6)
			strcpy(dst , "101");
		else if(L->dst_left == 7 && L->dst_right == 7)
			strcpy(dst , "110");
		else if(L->dst_left == 8 && L->dst_right == 8)
			strcpy(dst , "111");

		else if(L->dst_left == 1 && L->dst_right == 2)
			strcpy(dst , "00*");
		else if(L->dst_left == 3 && L->dst_right == 4)
			strcpy(dst , "01*");
		else if(L->dst_left == 5 && L->dst_right == 6)
			strcpy(dst , "10*");
		else if(L->dst_left == 7 && L->dst_right == 8)
			strcpy(dst , "11*");
		else if(L->dst_left == 1 && L->dst_right == 4)
			strcpy(dst , "0*");
		else if(L->dst_left == 5 && L->dst_right == 8)
			strcpy(dst , "1*");
		else
			strcpy(dst , "*");
	}
}
void choose_smallrange(int bits , char *ori , char *new , char *small){
	int ori_weight = 0;
	int new_weight = 0;
	if(bits == 2){
		if(strcmp(ori , "00") == 0 || strcmp(ori , "01") == 0 || strcmp(ori , "10") == 0 || strcmp(ori , "11") == 0)
			ori_weight = 1;
		else if(strcmp(ori , "0*") == 0 || strcmp(ori , "1*") == 0)
			ori_weight = 2;
		else if(strcmp(ori , "*") == 0)
			ori_weight = 3;
		
		if(strcmp(new , "00") == 0 || strcmp(new , "01") == 0 || strcmp(new , "10") == 0 || strcmp(new , "11") == 0)
			new_weight = 1;
		else if(strcmp(new , "0*") == 0 || strcmp(new , "1*") == 0)
			new_weight = 2;
		else if(strcmp(new , "*") == 0)
			new_weight = 3;
	}
	else if(bits == 3){
		if(strcmp(ori , "000") == 0 || strcmp(ori , "001") == 0 || strcmp(ori , "010") == 0 || strcmp(ori , "011") == 0 || strcmp(ori , "100") == 0 || strcmp(ori , "101") == 0 || strcmp(ori , "110") == 0 ||strcmp(ori , "111") == 0)
			ori_weight = 1;
		else if(strcmp(ori , "00*") == 0 || strcmp(ori , "01*") == 0 || strcmp(ori , "10*") == 0 || strcmp(ori , "11*") == 0)
			ori_weight = 2;
		else if(strcmp(ori , "0*") == 0 || strcmp(ori , "1*") == 0)
			ori_weight = 3;
		else if(strcmp(ori , "*") == 0)
			ori_weight = 4;
		
		if(strcmp(new , "000") == 0 || strcmp(new , "001") == 0 || strcmp(new , "010") == 0 || strcmp(new , "011") == 0 || strcmp(new , "100") == 0 || strcmp(new , "101") == 0 || strcmp(new , "110") == 0 ||strcmp(new , "111") == 0)
			new_weight = 1;
		else if(strcmp(new , "00*") == 0 || strcmp(new , "01*") == 0 || strcmp(new , "10*") == 0 || strcmp(new , "11*") == 0)
			new_weight = 2;
		else if(strcmp(new , "0*") == 0 || strcmp(new , "1*") == 0)
			new_weight = 3;
		else if(strcmp(new , "*") == 0)
			new_weight = 4;
	}

	if(ori_weight < new_weight){
		strcpy(small , ori);
	}
	else{
		strcpy(small , new);
	}

}
struct SwitchList *insert_Switch(struct LinkedList *MapRule , int capacity , int bits){
	struct SwitchList *List = NULL;
	char new_src[20];
	char new_dst[20];
	char ori_src[20];
	char ori_dst[20];
	transmation(bits , MapRule , new_src , new_dst);
	struct LinkedList *Rule = MapRule->next;
	while(Rule){
		long long int x = 1;
		for(int i = 0 ; i < Rule->index ; i++)
			x *= 2;
		long long int cal = MapRule->belongs;
		cal = cal / x;
		
		long long int cal2 = MapRule->part;
		cal2 = cal2 / x;

		if(cal % 2 == 0 && cal2 % 2 == 0){
			Rule = Rule->next;
			continue;
		}

		struct SwitchList *p = malloc(sizeof(struct SwitchList));
		transmation(bits , Rule , ori_src , ori_dst);
		char src_small[20];
		char dst_small[20];
		choose_smallrange(bits , ori_src , new_src , src_small);
		choose_smallrange(bits , ori_dst , new_dst , dst_small);

		strcpy(p->src , src_small);
		strcpy(p->dst , dst_small);
		strcpy(p->condition , Rule->condition);
		p->next = NULL;
	
			
		Rule = Rule->next;
		
		if(List == NULL){
			List = p;
			continue;
		}
		struct SwitchList *pre , *tmp = List;
		while(tmp){
			pre = tmp;
			tmp = tmp->next;
		}
		pre->next = p;
	}

	return List;
}
void print_map(struct LinkedList *MapRule){
	struct LinkedList *p = MapRule;
	while(p){
		printf("index:\t%d\n" , p->index);
		printf("utility:\t%lf\n" , p->utility);
		printf("all_cover_num:\t%d\n" , p->all_cover_num);
		printf("belongs:\t%Ld\n" , p->belongs);
		printf("condition:\t%s\n" , p->condition);

		printf("src_left:\t%d\n" , p->src_left);
		printf("src_right:\t%d\n" , p->src_right);
		printf("dst_left:\t%d\n" , p->dst_left);
		printf("dst_right:\t%d\n" , p->dst_right);
		printf("\n");
		p = p->next;
	}
}

int main(){
	int ingress_id , egress_id;
	int switch_id , switch_capacity;
	int switch_id1 , switch_id2 , weight;
	
	if(scanf("%d" , &bits_num)){};
	square = 1;
	for(int i = 0 ; i < bits_num ; i++)
		square = square * 2;
	if(scanf("%d %d" , &ingress_id , &egress_id)){};
	
	if(scanf("%d" , &switches_num)){};
	struct SwitchRule Switch[switches_num];
	for(int i = 0 ; i < switches_num ; i++){
		if(scanf("%d %d" , &switch_id , &switch_capacity)){};
		Switch[i].index = switch_id;
		Switch[i].capacity = switch_capacity;
		Switch[i].List = NULL;
	}

	if(scanf("%d" , &links_num)){};
	for(int i = 0 ; i < switches_num ; i++)
		for(int j = 0 ; j < switches_num ; j++)
			order[i][j] = 100000;
	for(int i = 0 ; i < links_num ; i++){
		if(scanf("%d %d %d" , &switch_id1 , &switch_id2 , &weight)){};
		order[switch_id1][switch_id2] = weight;
		order[switch_id2][switch_id1] = weight;
	}

	Dijkstra(ingress_id , switches_num);
	
	struct LinkedList *MapRule = NULL;
	if(scanf("%d" , &rule_num)){};
	for(int i = 0 ; i < rule_num ; i++){
		char *word1 = malloc(sizeof(char) * 100);
		char *word2 = malloc(sizeof(char) * 100);
		char *word3 = malloc(sizeof(char) * 100);
		if(scanf("%s %s %s" , word1 , word2 , word3)){};

		MapRule = insert_MapRule(MapRule , word1 , word2 , word3 , i + 1 , bits_num);
		free(word1);
		free(word2);
		free(word3);
	}
	
	int id = egress_id;
	int shortest[switches_num];
	for(int i = 0; i < switches_num ; i++)
		shortest[i] = -1;
	int short_id = 0;
	shortest[short_id] = id;
	while(id != ingress_id){
		id = path[id];
		short_id++;
		shortest[short_id] = id;
	}
	int left = 0;
	int right = switches_num - 1;
	while(left < right){
		if(shortest[right] == -1){
			right--;
			continue;
		}
		SWAP(shortest[left] , shortest[right]);
		left++;
		right--;
	}
	
	printf("%d\n" , short_id + 1);
	for(int i = 0 ; i < switches_num ; i++){
		if(shortest[i] == -1)
			continue;
		if(MapRule->src_left == 1 && MapRule->src_right == square && MapRule->dst_left == 1 && MapRule->dst_right == square)
			continue;
		
		//printf("---------------------------------------------------\n");
		//print_map(MapRule);
		//printf("---------------------------------------------------\n");
		struct LinkedList *MapUtility = NULL;
		MapUtility = struct_utility(MapRule , MapUtility , Switch[shortest[i]].capacity);
		
		if(MapUtility != NULL){
			//printf("---------------------------------------------------\n");
			//print_map(MapUtility);
			//printf("---------------------------------------------------\n");
			MapRule = insert_NewMapRule(MapRule , MapUtility);
			//printf("---------------------------------------------------\n");
			//print_map(MapRule);
			//printf("---------------------------------------------------\n");
		}
		Switch[shortest[i]].List = insert_Switch(MapRule , Switch[shortest[i]].capacity , bits_num);
	}

	//printf("---------------------------------------------------\n");
	//print_map(MapUtility);
	//printf("---------------------------------------------------\n");
	
	for(int i = 0 ; i < switches_num ; i++){
		if(shortest[i] == -1)
			continue;
		struct SwitchList *tmp = Switch[shortest[i]].List;
		int t = 0; //這顆switch用了多少空間
		while(tmp){
			t++;
			tmp = tmp->next;
		}
		printf("%d %d\n" , shortest[i] , t);
		tmp = Switch[shortest[i]].List;
		while(tmp){
			printf("%s %s %s\n" , tmp->src , tmp->dst , tmp->condition);
			tmp = tmp->next;
		}	
	}
	return 0;
}
