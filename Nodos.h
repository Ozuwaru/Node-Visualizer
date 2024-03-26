#include <iostream>
#include <vector>
#include <math.h>
#include<graphics.h>
/*
PROCESOS QUE DEBE CUMPLIR EL PROGRAMA:
-Ingresar pares ordenados de un grafo (padre, hijo)
-Ingresar datos desde una matriz de adyacencia
-Mostrar la matriz
-Mostrar el grafo*/





using namespace std;
class Node{
public:
	int v;
	int pX=0,pY=0,angle;
	vector<Node*> next;
	bool c=false;
	int pxS,pxI,pyS,pyI;
	
};

class Grafo{
public:
	vector<Node*> v;
	//le pasamos la posicion inicial del vector, en este caso 0, la posicion final y el numero a buscar
	int busquedaBinaria(int i, int d, int x){
		while (i <= d) {
	        int m = i + (d - i) / 2;
	 
	        if (v[m]->v == x)
	            return m;
	 
	        if (v[m]->v < x)
	            i = m + 1;
	 
	        else
	            d = m - 1;
	    }
	 
	    return INT_MIN;
	}
	
	
	void ordenamiento(){
		for(int i=v.size()-1;i>=0;i--){
			for(int j=i;j>=0;j--){
				if(v[i]->v<v[j]->v){
					Node* aux=v[j];
					v[j]=v[i];
					v[i]=aux;
					i=j;
				}
			}
		}
	}

	void verificarGuardar(Node *nodo1){
		int p1=busquedaBinaria(0,v.size()-1,nodo1->v);
		
		if(p1==INT_MIN){
			v.push_back(nodo1);
			ordenamiento();
		}else{
			if(nodo1->next.size()>0)
				v[p1]->next.push_back(nodo1->next[0]);
		}
	}
	
	void addNode(int n1,int n2){
		/*
			NECESITO UN ALGORITMO DE BUSQUEDA, AL AGREGAR NODOS QUE YA EXISTEN NO PUEDO RE INGRESARLOS
			Debo escribir un algoritmo que a la hora de ingresar pares, verifique si el nodo existe, alterar
			su informacion y repetir lo mismo para el segundo nodo, en caso contrario, puesto que no existen
			solo debo guardarlos en el vector
		*/
		
		Node *nodo1,  *nodo2;
		nodo1 = new Node;
		nodo2 = new Node;
		
		nodo1->v = n1;
		nodo2->v = n2;
		
		nodo1->next.push_back(nodo2);
		
		verificarGuardar(nodo1);
		verificarGuardar(nodo2);
		
		
		
	}
	
	static double d2r(double d) {
	  return (d / 180.0) * ((double) M_PI);
	}
	
	double sind(double x) {
	  if (!isfinite(x)) {
	    return sin(x);
	  }
	  if (x < 0.0) {
	    return -sind(-x);
	  }
	  int quo;
	  double x90 = remquo(fabs(x), 90.0, &quo);
	  switch (quo % 4) {
	    case 0:
	      // Use * 1.0 to avoid -0.0
	      return sin(d2r(x90)* 1.0);
	    case 1:
	      return cos(d2r(x90));
	    case 2:
	      return sin(d2r(-x90) * 1.0);
	    case 3:
	      return -cos(d2r(x90));
	  }
	  return 0.0;
	}
	
	
	void mostrarGrafo(int rp=150){
		//N numero de poligonos
		int N=v.size(); //Numero de Nodos
		cout<<endl<<N;
		//double rp= 150;
		double rA1= rp-10;
		double rA2= rp+10;
		int k = 0;//indice del Nodo
		int x= 1050, y= 350;
		int points[(N*2)+2];
		//int angles[N];
		int i=0;
		float param;
//		  result = sin (param*M_PI/180);
//		  printf ("The sine of %f degrees is %f.\n", param, result );
//		
		int j=0;
		for(i;i<N*2;i+=2){  
			param =((2 * 180.0 * j)/N);
			points[i]=(rp * cos(2 * M_PI * j / N) + x);
			
			
			v[i/2]->pxS=(rA1 * cos(2 * M_PI * j / N) + x);
			v[i/2]->pxI=(rA2 * cos(2 * M_PI * j / N) + x);
			
			//points[i+1]=( rp * sin((param/M_PI)*180 )+ y);
			points[i+1]=( rp *sind(param) + y);
			
			
			v[i/2]->pyS=( rA1 *sind(param) + y);
			v[i/2]->pyI=( rA2 *sind(param) + y);
			v[j]->angle=param;
			//cout<<points[i]<<" "<<points[i+1];
			j++;
		}
		settextjustify(1,1);
		char vNodo[4];
//			for(i=0;i<N*2;i+=2){
//				//line(points[i],points[i+1], points[i+2],points[i+3]);
//				x=points[i];
//				y=points[i+1];
//				
//				circle(x,y,25);
//				sprintf(vNodo, "%d", v[k]->v);
//				outtextxy(x,y+8,vNodo);
//				v[k]->pX=x;
//			//	cout<<endl<<"->"<<i;
//				v[k]->pY=y;
//				k++;
//			}
//		}
		
		for(int i=0;i<v.size();i++){
			
			if(v[i]->next.size() >0 ){
				
				for(int j=0;j<v[i]->next.size();j++){
					k= busquedaBinaria(0,v.size(),v[i]->next[j]->v);
					bool dC=false;
					
					if(v[i]->v	<	v[k]->v){
						if(v.size()==2){
							line(v[i]->pxS,v[i]->pyS-10,v[k]->pxS,v[k]->pyS-10);
							
						}else{
							
							line(v[i]->pxS,v[i]->pyS,v[k]->pxS,v[k]->pyS);
						}
					}else{
						if(v.size()==2){
							line(v[i]->pxI,v[i]->pyI+10,v[k]->pxI,v[k]->pyI+10);
							
						}
						else{
							line(v[i]->pxI,v[i]->pyI,v[k]->pxI,v[k]->pyI);
							
						}
						//line(pointsA2[i],pointsA2[i+1],pointsA2[k],pointsA2[k+1]);
					}
						//continue;
						
					
					
					//AQUI DBEMOS DIBUJAR EL TRIANGULO
//					arc(200, 200, 35, 145, 150);
//   				arc(200, 50, 215, 325, 150);

					
				}
			}

			

//
		}
		k=0;
		for(i=0;i<N*2;i+=2){
				//line(points[i],points[i+1], points[i+2],points[i+3]);
				x=points[i];
				y=points[i+1];
				setfillstyle(SOLID_FILL,WHITE); 
				//setcolor(WHITE);
				bar(x-20, y-20, x + 20, y + 20);
				//setcolor(BLACK);
				circle(x,y,25);
				//floodfill(x,y,BLACK);
				sprintf(vNodo, "%d", v[k]->v);
				outtextxy(x,y+8,vNodo);
				v[k]->pX=x;
			//	cout<<endl<<"->"<<i;
				v[k]->pY=y;
				k++;
			}
		
	}
	
	
	
	Grafo(){
//		
//		
//		this->addNode(10,5);
//		this->addNode(5,5);
//		this->addNode(5,8);
//		this->addNode(8,5);
//		this->addNode(10,8);
//		//cout<<v.size();
//		for(int i=0;i<v.size();i++){
//			//cout<<i;
//			
//			cout<<"Nodo numero #"<<i+1<<" "<<v[i]->v<<endl;
//			if(v[i]->next.size() >0 ){
//				cout<<"Esta conectado con los nodos: "<<endl;
//				for(int j=0;j<v[i]->next.size();j++){
//					cout<<v[i]->next[j]->v<<endl;
//					
//				}
//			}
//			cout<<endl;
//		}
	}
	
	
	void matrizAdyacencia(int iX, int iY){
		
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(DARKGRAY);
		
		//outtextxy(700,100,"Menu de Ingreso")
        //bar(500, 500, 1200, 600);
        setlinestyle(SOLID_LINE,0,3);
        
        int fX= iX+(40*v.size());
        int fY= iY+(30*v.size());
        line(iX,iY,fX,iY);
        line(iX,iY,iX,fY);
        line(fX,iY,fX,fY);
        line(iX,fY,fX,fY);
        
        //CADA COLUMNA MEDIRA 30 PIXELES
        char n[5]= "";
        bool e=false;
        for(int i=0;i<v.size();i++){
        	
        	sprintf(n, "%d", v[i]->v);
        	
        	outtextxy(15+iX+(40*i),iY-10,n);
        	outtextxy(iX-20,20+iY+(30*i) ,n);
        	
        	
        	for(int j=0;j<v.size();j++){
        		e=false;
        		int caminos=0;
        		for(int z=0;z<v[i]->next.size();z++){
        			if(v[i]->next[z]->v == v[j]->v){
        				caminos++;
        				e=true;
					}
				}
				if(!e){
        			sprintf(n, "%d", 0);
				}else{
					sprintf(n, "%d", caminos);
			        //outtextxy(15+iX+(40*j),23+iY+(30*i),n);
				}
			        outtextxy(15+iX+(40*j),23+iY+(30*i),n);
			}
		}
	}
	void matrizIncidencia(int iX, int iY){
		
		setfillstyle(SOLID_FILL, BLACK);
		setcolor(DARKGRAY);
		
		//outtextxy(700,100,"Menu de Ingreso")
        //bar(500, 500, 1200, 600);
        setlinestyle(SOLID_LINE,0,3);
        vector<int> caminos;
        int c=1;
        for(int i=0;i<v.size();i++){
        		
	        	for(int j=0;j<v[i]->next.size();j++){
			        caminos.push_back(c);
			        caminos.push_back(v[i]->v);
	        		caminos.push_back(v[i]->next[j]->v);
	        		c++;
				}
        	
		}
		cout<<caminos.size();
        int fX= iX+(40*caminos.size()/3);
        int fY= iY+(30*v.size());
        line(iX,iY,fX,iY);
        line(iX,iY,iX,fY);
        line(fX,iY,fX,fY);
        line(iX,fY,fX,fY);
		c=0;
        
        //CADA COLUMNA MEDIRA 30 PIXELES
        char n[5]= "";
        bool e=false;
        for(int i=0;i<v.size();i++){
        	
        	
        		sprintf(n, "%d", v[i]->v);
        	outtextxy(iX-20,20+iY+(30*i) ,n);
		}
		
		for(int i=0;i<caminos.size(); i+=3){
	        	string a="e"+to_string(i/3+1);
        		char * temp = const_cast<char*> ( a.c_str() );
        		outtextxy(20+iX+(40*i/3),iY-10,temp);
        		

				for(int j=0;j<v.size();j++){
					bool e=false;
					for(int z=0;z<v[j]->next.size();z++){
						if(v[j]->next[z]->v  == caminos[i+2]  &&  v[j]->v == caminos[i+1]){
							e=true;
							break;
						}
					}
					if(e){
						sprintf(n, "%d", 1);
					}else{
						sprintf(n, "%d", 0);
						
					}
					outtextxy(20+iX+(40*i/3),23+iY+(30*j),n);
				}
			}
			c+=3;
	}
	
	
};

