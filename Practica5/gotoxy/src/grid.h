//
// Created by salabeta on 24/11/20.
//

#ifndef GOTOXY_GRID_H
#define GOTOXY_GRID_H

#include <QGraphicsItem>

template <typename HMIN, HMIN hmin, typename WIDTH, WIDTH width, typename TILE, TILE tile>
class Grid
{
public:
    Grid()
    {
        array.resize((int)(width / tile));
        for (auto &row : array)
            row.resize((int)(width / tile));
        int k = 0;
        for (int i = hmin; i < width / 2; i += tile, k++)
        {
            int l = 0;
            for (int j = hmin; j < width / 2; j += tile, l++)
            {
                array[k][l] = Value{false, false, nullptr, nullptr, i, j};
            }
        }
    };

    struct Value
    {
        bool occupied = false;
        bool pasado = false;
        QGraphicsRectItem *paint_cell = nullptr;
        QGraphicsTextItem *text_cell = nullptr;
        int cx, cy;
        int k, l;     // inicializar estos valores al crear el elemento
        int dist = 0; //dist vecinos
    };

    std::vector<std::vector<Value>> array;


void create_graphic_items(QGraphicsScene &scene, QGraphicsView *view)
{
   auto fondo = QColor("LightGreen"); fondo.setAlpha(40);
   QFont font("Bavaria");
   font.setPointSize(40);
   font.setWeight(QFont::TypeWriter);
   for (auto &row : array)
       for (auto &elem : row)
       {
           elem.paint_cell = scene.addRect(-tile / 2, -tile / 2, tile, tile, QPen(QColor("DarkGreen")), QBrush(fondo));
           elem.paint_cell->setPos(elem.cx, elem.cy);
           elem.text_cell = scene.addText("", font);
           elem.text_cell->setPos(elem.cx-tile/2, elem.cy-tile/2);
           // Get the current transform
           QTransform transform(elem.text_cell->transform());
           qreal m11 = transform.m11();    // Horizontal scaling
           qreal m12 = transform.m12();    // Vertical shearing
           qreal m13 = transform.m13();    // Horizontal Projection
           qreal m21 = transform.m21();    // Horizontal shearing
           qreal m22 = transform.m22();    // vertical scaling
           qreal m23 = transform.m23();    // Vertical Projection
           qreal m31 = transform.m31();    // Horizontal Position (DX)
           qreal m32 = transform.m32();    // Vertical Position (DY)
           qreal m33 = transform.m33();    // Addtional Projection Factor
           // Vertical flip
           m22 = -m22;
           // Write back to the matrix
           transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
           // Set the items transformation
           elem.text_cell->setTransform(transform);
       }
}

void pintarNumeritos(QGraphicsScene &scene, QGraphicsView *view,int x,int z)
{
   QFont font("Tokyo");
   font.setPointSize(40);
   font.setWeight(QFont::TypeWriter);
   for (auto &row : array)
       for (auto &elem : row)
       {       elem.pasado=false; 
               elem.dist= (sqrt(pow((elem.cx - x), 2) + pow((elem.cy - z), 2)))/100;
       	if(elem.occupied==true){ 
       	elem.paint_cell->setBrush(Qt::red);
       	QString s = QString::number(elem.dist);
           	elem.paint_cell = scene.addRect(-tile / 2, -tile / 2, tile, tile, QPen(QColor("DarkGreen")));
           	elem.paint_cell->setPos(elem.cx, elem.cy);
           	elem.text_cell = scene.addText(s, font);
           	elem.text_cell->setPos(elem.cx-tile/2, elem.cy-tile/2);
       	}
       	else{
           QString s = QString::number(elem.dist);
           std::cout << elem.cx<< " "<<elem.cy << " " << elem.dist << " " << x << " "<< z <<endl;
           elem.paint_cell = scene.addRect(-tile / 2, -tile / 2, tile, tile, QPen(QColor("DarkGreen")));
           elem.paint_cell->setPos(elem.cx, elem.cy);
           elem.paint_cell->setBrush(Qt::white);
           elem.text_cell = scene.addText(s, font);
           elem.text_cell->setPos(elem.cx-tile/2, elem.cy-tile/2);
           }
           // Get the current transform
           QTransform transform(elem.text_cell->transform());
           qreal m11 = transform.m11();    // Horizontal scaling
           qreal m12 = transform.m12();    // Vertical shearing
           qreal m13 = transform.m13();    // Horizontal Projection
           qreal m21 = transform.m21();    // Horizontal shearing
           qreal m22 = transform.m22();    // vertical scaling
           qreal m23 = transform.m23();    // Vertical Projection
           qreal m31 = transform.m31();    // Horizontal Position (DX)
           qreal m32 = transform.m32();    // Vertical Position (DY)
           qreal m33 = transform.m33();    // Addtional Projection Factor
           // Vertical flip
           m22 = -m22;
           // Write back to the matrix
           transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
           // Set the items transformation
           elem.text_cell->setTransform(transform);
       }
}

    /*
 * Inicializamos el array a false, osea, no ocupadas.
 */
    void inicializate()
    {
        for (int i = 0; i < 50; ++i)
        {
            for (int j = 0; j < 50; ++j)
            {
                this->array[i][j].occupied = false;
            }
        }
    }

     std::optional<std::tuple<int, int>> neighboors(int i,int j)
	{
	std::vector<std::tuple<int, int>> lista_coor_de_vecinos{ {0,-1},{1,0},{-1,0},{0,1},{-1,-1}, {1,-1}, {-1,1}, {-1,1},{1,1} };
	
	int min = 9999;
	int kz = 0;
	int lz = 0;
	for(auto [dk, dl] : lista_coor_de_vecinos)
	{
     		int k = i + dk;        // OJO hay que añadir al struct Value las coordenadas de array
     		int l = j + dl;  
     		if( ((k >= 0) && (k < 50)) && ((l >= 0) && (l < 50)) && this->array[k][l].occupied==false && this->array[k][l].dist < min && this->array[k][l].pasado == false) 
     		{ 
			min = this->array[k][l].dist;
			kz = k;
			lz = l;
     		} 
	}  
	return std::make_tuple(kz, lz);
	}


public:
    /**
     * modificamos en funcion de v la coordenada x,z
     * @param x
     * @param z
     * @param v
     */
    void set_Value(int x, int z, bool v)
    {
        // this->array[x][z] = v;
        //auto [i, j] = transformar(x,z);
        //array[i][j].occupied = v;
        //if(v)
        //     array[i][j].paint_cell->setColor(QColor());
    }
    /**
     * devolvemos el valor de la coordenada x,z
     * @param x
     * @param z
     * @return
     */
    bool get_value(int x, int z)
    {
        //auto [i, j] = transformar(x,z);
        //return  this->array[x][z];
        return true;
    }

    void set_occupied(int x, int z)
    {
        this->array[x][z].occupied = true;
    }
};

#endif //GOTOXY_GRID_H
