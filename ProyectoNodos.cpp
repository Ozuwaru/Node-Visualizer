
#include "Nodos.h"
class Cuadro {
private:
    char texto[50];
    int x, y, ancho, alto;

public:

    bool clickVer(int mouseX, int mouseY) {
        return (mouseX >= x-(x/2) && mouseX <= x + ancho && mouseY >= y && mouseY <= y + alto);
    }
    void dibujar() {
    	setbkcolor(8);
    	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    	setfillstyle(SOLID_FILL, 8);
		setcolor(8);
        bar(x-(ancho/2), y, x + (ancho/2), y + alto);
        setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
       // outtextxy(x + 10, y + 10, texto);
       	settextjustify(1,2);
        outtextxy(x, y+10 , texto);
        setbkcolor(WHITE);
    }

    
    Cuadro(int x, int y, int ancho, int alto, const char* texto) {
        this->x = x;
        this->y = y;
        ancho =ancho *15;
        this->ancho = ancho;
        this->alto = alto;
        strcpy(this->texto, texto);
    }
};


class Interfaz{
private:
	const int ancho = 1400;
	const int alto = 700;
	Grafo g;
public:
	Cuadro mostrarC(string info, int x,int y){
		int c= info.size();
		Cuadro ingreso(x,y,c,50,info.c_str());
		//ingreso.dibujar();
		return ingreso;
	}
	int leerBoton(int &pX, int &pY, vector<Cuadro>botones){
		
		getmouseclick(WM_LBUTTONDOWN, pX, pY);
		for(int i=0;i<botones.size();i++){
		
		    if(botones[i].clickVer(pX,pY)){
		    	return i;
			}
			           	
		}
					
		return INT_MIN;			
		    
	}
	int leerN(int x, int y){
		char *charArr;
		string b;
		char a;
		settextjustify(0,2);
		while(true){
			if(kbhit()){
				a=getch();
				if(a!='\r' && isdigit(a)){
			 		b+=a;
									    			
				}
				else if( a=='\r'){
					break;
				}
				charArr =const_cast<char*> ( b.c_str() );
				outtextxy(x,y,charArr);
			}
		}
								
		int number = stoi(b);
		settextjustify(1,2);
		return number;
	}
	Interfaz(){
		initwindow(ancho,alto,"Nodos");
		setbkcolor(WHITE);
		cleardevice();
		vector <Cuadro> botonesMenu;
		
		vector <Cuadro> botonesIngreso;
		setcolor(DARKGRAY);
		settextjustify(1,0);
		settextstyle(BOLD_FONT,HORIZ_DIR,5);
		//outtextxy(700,100,"Creador de Grafos");
		
		botonesMenu.push_back(mostrarC("Node pair input",700,350));
		
		botonesMenu.push_back(mostrarC("Graph Visualizer",700,410));
		
		botonesMenu.push_back(mostrarC("Exit",700,470));
		
		
		
		botonesIngreso.push_back(mostrarC("Input Pair",450,350));
		int pX, pY;
		
		int v=0;
		
		for(int i=0;i<botonesMenu.size();i++){
			botonesMenu[i].dibujar();
		}	
		bool terminated=false;
		while(!terminated){
			switch(v){ 
				case 0:{
					cleardevice();
					setcolor(DARKGRAY);
					settextjustify(1,0);
					settextstyle(BOLD_FONT,HORIZ_DIR,5);
					outtextxy(700,100,"Graph Visualizer");
					settextstyle(BOLD_FONT,HORIZ_DIR,2);
					outtextxy(700,600,"Made By: Oswald Torrealba");
					for(int i=0;i<botonesMenu.size();i++){
						botonesMenu[i].dibujar();
					}
		
				 
					
					while(true){
						if (ismouseclick(WM_LBUTTONDOWN)) {
							int r =leerBoton(pX,pY,botonesMenu);
							
							if(r==0){
								v=1;
								cleardevice();
							}else if(r==1){
								cleardevice();
								v=2; 
							}else if(r==2){
								terminated=true;
							}
							break;
						}
						delay(100);
					}
	        
					break;
				}
				
				case 1:{
					setcolor(DARKGRAY);
					settextjustify(1,0);
					settextstyle(BOLD_FONT,HORIZ_DIR,5);
					
//					for(int i=0;i<botonesIngreso.size();i++){
//						botonesIngreso[i].dibujar();
//					}
//					
//					while(true){
//						if (ismouseclick(WM_LBUTTONDOWN)) {
//							int r =leerBoton(pX,pY,botonesIngreso);
//							
//							if(r==0){
								/*
									Ingresar Pares
								*/ 
								cleardevice();
								
								setcolor(DARKGRAY);
								settextstyle(BOLD_FONT,HORIZ_DIR,2);
								outtextxy(300,50,"(Press Enter)");
								settextstyle(BOLD_FONT,HORIZ_DIR,5);
								outtextxy(700,100,"Input Menu");
								
								settextstyle(BOLD_FONT,HORIZ_DIR,2);
								outtextxy(300,200,"Input the exiting Node: ");
								int n1 =leerN(650,200);
								outtextxy(300,250,"Input the arriving : ");
								int n2 =leerN(650,250);
								g.addNode(n1,n2);
								
								g.mostrarGrafo();
								outtextxy(200,350,"Adjacent Nodes Matrix");
								g.matrizAdyacencia(40,400);
								outtextxy(500,350,"Colliding Nodes Matrix");
								g.matrizIncidencia(450,400);
								vector<Cuadro> conf;
								conf.push_back(mostrarC("Continue", 1050, 600));
								conf[0].dibujar();
								while(true){
									
									if (ismouseclick(WM_LBUTTONDOWN)) {
										int r =leerBoton(pX,pY,conf);
										if(r==0){
											v=0;
											break;
										}
									}
									delay(100);
								}
//							}else if(r==1){
//								v=0;
//								
//							}
//							
							//delay(5000);
							break;
						
						delay(100);
					//}
					break;
				}
				case 2:{
					//Aqui dibujaremos la matriz de adyacencia y de incidencia y dibujaremos el nodo, pero mas grande
					setcolor(DARKGRAY);
					settextstyle(BOLD_FONT,HORIZ_DIR,5);
								outtextxy(700,50,"Graph Visualizer");
								
								settextstyle(BOLD_FONT,HORIZ_DIR,2);
								g.mostrarGrafo(200);
								outtextxy(350,150,"Adjacent Nodes Matrix");
								g.matrizAdyacencia(260,200);
								outtextxy(350,400,"Colliding Nodes Matrix");
								g.matrizIncidencia(260,450);
								vector<Cuadro> conf;
								conf.push_back(mostrarC("Continue", 1050, 600));
								conf[0].dibujar();
								while(true){
									
									if (ismouseclick(WM_LBUTTONDOWN)) {
										int r =leerBoton(pX,pY,conf);
										if(r==0){
											v=0;
											break;
										}
									}
									delay(100);
								}
					break;
				}
			}
			
			//cout<<v<<endl;
			
		
		
		}
		
		closegraph();
	} 
};

   
int main(){
	
	Interfaz();
	
	
	return 0;
}