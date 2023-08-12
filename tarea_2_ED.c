#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodetree{//Estructura de nodo binario
    int key;
    char name[40];
    char ticket[45];
    struct nodetree *left;
    struct nodetree *right;
}NODET;


void display_menu(); //Prototipo mostrar menu
NODET *newnode(NODET *rtree, int id);//Prototipo funcion Nuevo nodo
NODET *insertree(NODET *rtree, int id);//Prototipo funcion insertar nodo en el arbol binario
NODET *mininum(NODET *renode);//Prototipo funcion para encontrar el nodo mas a la izquierda
NODET *esearching(NODET *rtree, int en);//Prototipo funcion para buscar nodo e eliminarlo
void searchingforid(NODET *rtree, int id2); //Prototipo funcion para encontrar por ID
void searchingfordest(NODET *rtree, char boleto[]); //Prototipo funcion para encontrar por destino
void inorden(NODET *rtree); //Prototipo mostrar vuelos ordenados
void treefree(NODET *rtree); //Protipo para liberar memoria

int main(){
    NODET *rtree=NULL;//Raiz del arbol
    int menu,id,id2,en,leave;
    char boleto[45];
    do{
        system("cls");
        display_menu();
        scanf("%d",&menu);
        fflush(stdin);
        switch (menu){
        case 1://Opcion 1 Realizar reserva del vuelo
            printf("\n\tSu identificacion de boleto:\t\n>");
            scanf("%d",&id);
            rtree=insertree(rtree,id);
            system("pause");
            break;
        case 2://Opcion 2 Cancelar reserva del vuelo
            if(rtree==NULL){
                printf("\n\tNo hay vuelos registrados\t\n>");
                system("pause");
                break;
			}
			printf("\n\tNumero de su reserva para cancelar\t\n>");
            scanf("%d",&en);
            rtree=esearching(rtree,en);
            system("pause");
            break;
        case 3://Opcion 3 Buscar reserva del vuelo
            if(rtree==NULL){
                printf("\n\tNo hay vuelos registrados\t\n>");
                system("pause");
                break;
			}
			printf("\n\tNumero de reserva que desea buscar:\t\n>");
			scanf("%d",&id2);//Busqueda de ID==key
            searchingforid(rtree,id2);
            system("pause");
            break;
        case 4://Mostrar reservas por destino del vuelo
            if(rtree==NULL){
                printf("\n\tNo hay vuelos registrados\t\n>");
                system("pause");
                break;
			}
			printf("\n\tNombre del destino que desea buscar\t\n>");
            fflush(stdin);
            fgets(boleto, sizeof(boleto),stdin);
            boleto[strcspn(boleto,"\n")]= '\0';
            searchingfordest(rtree,boleto);
            system("pause");
            break;
        case 5://Mostrar reservas ordenadas del vuelo
            if(rtree==NULL){
                printf("\n\tNo hay vuelos registrados\t\n>");
                system("pause");
                break;
			}
            printf("\n\tEstos son los vuelos en orden de ID:\t\n");
            printf("ID\t|\tDestino\t\t|Nombre del comprador|\n");
            inorden(rtree);// Muestra en inorden los vuelos
            system("pause");
            break;
        case 6:
            leave=1; //Salir del switch
            break;
        default:
        printf("\n\tNumero ingresado incorrecto. intente nuevamente.\n\t"); //Ingreso incorrecto
        system("pause");
            break;
        }
    }while(leave==0);
    treefree(rtree);
    return 0;
}

//Funcion mostrar menu
void display_menu(){
    printf("\n_______________________\tBienvenido aventurero a Vuelos De Dragon!_______________________\n");
    printf("\t\n1.-Realizar reserva de vuelo\n2.-Cancelar reserva de vuelo\n3.-Buscar reserva de vuelo por numero \n4.-Buscar reserva por destino\n5.-Reservas por orden de llegada\n6.-Salir\n\t");
    printf("\n\t__________________________________________________\t\n>");
}
//Funcion para crear nodos en un arbol binario
NODET *newnode(NODET *rtree,int id){
    NODET *nuevo;
        nuevo=(NODET*)malloc(sizeof(NODET));
        printf("\n\tDestino a:\t\n>");
        fflush(stdin);
        scanf(" %[^\n]",&nuevo->ticket);
        printf("\n\tSu nombre:\t\n>");
        fflush(stdin);
        scanf(" %[^\n]",&nuevo->name);
        nuevo->key=id;
        nuevo->left=NULL;
        nuevo->right=NULL;
    return nuevo;
}

//Funcion de insercion
NODET *insertree(NODET *rtree, int id){
    if (rtree==NULL){
        return newnode(rtree,id);
    }else{
        if(id<rtree->key){
            rtree->left=insertree(rtree->left,id);
        }else if (id>rtree->key){
            rtree->right=insertree(rtree->right,id);
        }else{
            printf("\n\tID ya existe, intente nuevamente\n\t");
        }
        return rtree;
    }
}
//Funcion para recorrer en in-post orden y reemplazar al nodo eliminado para mantener estructura
NODET *mininum(NODET *renode){
    if (renode->left!=NULL){
        return mininum(renode->left);
    }else{
        return renode;
    }
}
//Funcion para buscar e eliminar nodo en ABB
NODET *esearching(NODET *rtree, int en){
    NODET *aux;
    if (rtree==NULL){//Arbol vacio
        printf("\n\tNo hay vuelo para eliminar, intente nuevamente\n\t");
        return rtree;
    }else if(en<rtree->key){//Buscando por izquierda
        rtree->left=esearching(rtree->left,en);
    }else if(en>rtree->key){ //Buscando por derecha
        rtree->right=esearching(rtree->right,en);
    }else{//Encuentro el nodo para eliminar 
        if (rtree->left==NULL){//Si no hay a la izquierda, reemplazo con el hijo derecho//Caso hijo unico
            aux=rtree->right;
            free(rtree);
            printf("\n\tSe ha cancelado la reserva\n\t");
            return aux;
        }else if(rtree->right==NULL){//Si no hay a la derecha, reemplazo con el hijo izquierdo//Caso hijo unico
            aux=rtree->left;
            free(rtree);
            printf("\n\tSe ha cancelado la reserva\n\t");
            return aux;
        }
        aux=mininum(rtree->right);//Si tiene dos hijos
        rtree->key=aux->key;
        strcpy(rtree->name,aux->name);
        strcpy(rtree->ticket,aux->ticket);
        rtree->right=esearching(rtree->right,aux->key);
        printf("\n\tSe ha cancelado la reserva\n\t");
    }
    return rtree;
}

//Funcion para encontrar el vuelo con la id
void searchingforid(NODET *rtree, int id2){
    if (rtree!=NULL){
        searchingforid(rtree->left,id2);
        if (rtree->key==id2){
        printf("ID\t|\tDestino\t\t|Nombre del comprador\n");
        printf("%d\t|\t%s\t\t|%s\t\n",rtree->key,rtree->ticket, rtree->name);
        }
        searchingforid(rtree->right,id2);
    }
}

//Funcion para encontrar el vuelo con el destino
void searchingfordest(NODET *rtree, char boleto[]){
    if (rtree!=NULL){
        searchingfordest(rtree->left,boleto);
        if (strcmp(rtree->ticket,boleto) ==0){
            printf("ID\t|\tDestino\t\t|Nombre del comprador\n");
            printf("%d\t|\t%s\t\t|%s\t\n",rtree->key,rtree->ticket, rtree->name);
        }
        searchingfordest(rtree->right,boleto);
    }
}

//Funcion inorden 
void inorden(NODET *rtree){
    if (rtree!=NULL){
        inorden(rtree->left);
        printf("%d\t|\t%s\t\t|\t%s\t|\n",rtree->key,rtree->ticket, rtree->name);
        inorden(rtree->right);
    }
}

//Funcion liberacion de memoria 
void treefree(NODET *rtree){
    if (rtree!=NULL){
        treefree(rtree->left);
        treefree(rtree->right);
        free(rtree);
    }
}
