#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
//pollo
typedef std::vector<double> length; 

double average (length);
double uncertainty (double, int);
double angle (double s, double h);
double angle_unty (double s, double ds, double h, double dh);
double radius (double dist, double phi1, double phi2);
double radius_unty (double d, double phi1, double phi2, double dphi1, double dphi2);
double gravity(double length, double period);

int main(int argc, char **argv)
{
	//numero de datos que fueron tomados para s, h y l
	const int N = 5;
	
	//numero de datos tomados para el periodo T
	
	const int NT = 10;
	
    //se declaran los vectores que van a guardar las mediciones
    length s1(N, 0.0);
    length s2(N, 0.0);
    length s3(N, 0.0);
    length s4(N, 0.0);
    length h1(N, 0.0);
    length h2(N, 0.0);
    length h3(N, 0.0);
    length h4(N, 0.0);

	//vectores para datos de L
	length l1(N, 0.0);
    length l2(N, 0.0);
	length l3(N, 0.0);
	length l4(N, 0.0);
	
	//vectores para datos de T
	
	length T1(NT, 0.0);
    length T2(NT, 0.0);
	length T3(NT, 0.0);
	length T4(NT, 0.0);
	
    //falta fijar la precision de cout
    double avs1 = 0.0, avs2 = 0.0, avs3 = 0.0, avs4 = 0.0, avh1 = 0.0, avh2 = 0.0, avh3 = 0.0, avh4 = 0.0, avl1 = 0.0, avl2 = 0.0, avl3 = 0.0, avl4 = 0.0; //se crean variables para los promedios de high (h), shadow (s) y lenght (l)
    double avT1 = 0.0, avT2 = 0.0, avT3 = 0.0, avT4 = 0.0; //se crean variables para guardar los promedios para los periodos de oscilacion
	double angle1 = 0.0, angle2 = 0.0, angle3 = 0.0, angle4 = 0.0; //se crean variables para guardar angulos formados por la altura del objeto y su sombra
    double dangle1 = 0.0, dangle2 = 0.0, dangle3 = 0.0, dangle4 = 0.0; //variables para guardar la incertidumbre en la medicion del angulo
    double dB_A = 137470, dB_Az = 212270, dB_C = 90590, dA_Az = 348050, dA_C = 46900, dC_Az = 302000; //variables para la distancia (N-S) que separa las distintas ciudades
    double rB_A = 0.0, rB_Az = 0.0, rB_C = 0.0, rA_Az = 0.0, rA_C = 0.0, rC_Az = 0.0; //variables para el radio segun los valores medidos en cada ciudad
    double drB_A = 0.0, drB_Az = 0.0, drB_C = 0.0, drA_Az = 0.0, drA_C = 0.0, drC_Az = 0.0; //variables para incertidumbre en el radio
 
	double gA = 0.0, gAz = 0.0, gB = 0.0, gC = 0.0;
 
    const double delta = std::atof(argv[1]); //lee incertidumbre de medicion de s y h desde la terminal
	const double deltal = std::atof(argv[2]); //lee la incertidumbre de medicion de l desde la terminal
	double deltaf = 0.0; //variable para guardar incertidumbre total cuando se promedien s y h

    //vectores para almacenar valores individuales de los radios y sus incertidumbres, tienen como objetivo poder aplicar la funcion average

    length avgr(6, 0.0);
    length avgdr(6, 0.0);

    double rf = 0.0; //guarda el radio de la tierra segun las mediciones en distintas ciudades
    double drf = 0.0; //guarda la inertidumbre de medicion del radio de la tierra entre las zonas medidas

    std::cout << "Los valores ingresados fueron: " << "\n";
    std::cout << "s1(A)" << "\t" << "h1(A)" << "\t" << "l1(A)" << "\t" << "s2(Az)" << "\t" << "h2(Az)" << "\t" << "l2(Az)" << "\t" << "s3(B)" << "\t" << "h3(B)" << "\t" << "l3(B)" << "\t" << "s4(C)" << "\t" << "h4(C)" << "\t" << "l4(C)" << "\n"; //imprime en consola los datos ingresados para poder verificar    std::ifstream fin ("input.txt");

    std::ifstream fin ("input.txt");
    
    fin.precision(4); //esta precision depende de como se mida
    fin.ignore(1000,'#'); //esta linea es para organizar el .txt e ingresar los datos mas facilmente
    
    for(int ii = 0; ii <= N-1; ++ii) //ingresa los datos en el .txt al vectores en el programa
    {
        fin >> s1[ii]; //como fstream barre por filas, se deja que se haga el barrido por filas y cada vez se ingresa cada valor en un vector distinto, con esto se simula que lee
        std::cout << s1[ii] << "\t"; //por columnas, la estrucutra por colummnas en el txt es mas facil de leer para nosotros
        fin >> h1[ii];
        std::cout << h1[ii] << "\t";
        fin >> l1[ii];
        std::cout << l1[ii] << "\t";
		fin >> s2[ii];
        std::cout << s2[ii] << "\t";
        fin >> h2[ii];
        std::cout << h2[ii] << "\t";
        fin >> l2[ii];
        std::cout << l2[ii] << "\t";
		fin >> s3[ii];
        std::cout << s3[ii] << "\t";
        fin >> h3[ii];
        std::cout << h3[ii] << "\t";
        fin >> l3[ii];
        std::cout << l3[ii] << "\t";
		fin >> s4[ii];
        std::cout << s4[ii] << "\t";
        fin >> h4[ii];
        std::cout << h4[ii] << "\t";
		fin >> l4[ii];
        std::cout << l4[ii] << "\n";
	}
    
    fin.close();
	
	std::cout << "\n" << "Para las longitudes, y " << "\n";
	std::cout << "T1(A)" << "\t" << "T2(Az)" << "\t" << "T3(B)" << "\t" << "T4(C)" << "\n"; //imprime en consola los datos ingresados para poder verificar std::ifstream finT ("input2.txt");

	
	std::ifstream finT ("input2.txt"); //lee los datos para el periodo de oscilacion
    
    finT.precision(4); //esta precision depende de como se mida
    finT.ignore(1000,'#'); //esta linea es para organizar el .txt e ingresar los datos mas facilmente
    
    for(int ii = 0; ii <= NT-1; ++ii) //ingresa los datos en el .txt al vectores en el programa
    {
        finT >> T1[ii]; //como fstream barre por filas, se deja que se haga el barrido por filas y cada vez se ingresa cada valor en un vector distinto, con esto se simula que lee
        std::cout << T1[ii] << "\t"; //por columnas, la estrucutra por colummnas en el txt es mas facil de leer para nosotros
        finT >> T2[ii];
        std::cout << T2[ii] << "\t";
        finT >> T3[ii];
        std::cout << T3[ii] << "\t";
		finT >> T4[ii];
        std::cout << T4[ii] << "\n";
	}
    
    fin.close();
	
	std::cout << "\n" << "Para los periodos de oscilacion" << std::endl;

    deltaf = uncertainty(delta, N); //calcula la incertidumbre total despues de hacer el promedio
	//deltafl = uncertainty(deltal, N); //calcula la incertidumbre total despues de hacer el promedio

    //se calculan los promedios para cada conjunto de datos

    avs1 = average(s1);
    avh1 = average(h1);
    avl1 = average(l1);
	avs2 = average(s2);
    avh2 = average(h2);
    avl2 = average(l2);
	avs3 = average(s3);
    avh3 = average(h3);
    avl3 = average(l3);
	avs4 = average(s4);
    avh4 = average(h4);
	avl4 = average(l4);

    //se calcula aproximadamente el angulo de incidencia de la luz solar el dia y la hora de la medicion en cada lugar

    angle1 = angle(avs1,avh1);
    angle2 = angle(avs2,avh2);
    angle3 = angle(avs3,avh3);
    angle4 = angle(avs4,avh4);

    //se calcula la incetidumbre para cada angulo de incidencia
    
    dangle1 = angle_unty(avs1,deltaf,avh1,deltaf);
    dangle2 = angle_unty(avs2,deltaf,avh2,deltaf);
    dangle3 = angle_unty(avs3,deltaf,avh3,deltaf);
    dangle4 = angle_unty(avs4,deltaf,avh4,deltaf);
    
    //std::cout << angle1 << " +/- " << dangle1  << "\n";

    //se calcula el radio segun las ciudades para las que se midieron los angulos

    rB_A = radius(dB_A,angle3,angle1);
    drB_A = radius_unty(dB_A,angle3,angle1,dangle3,dangle1);
    rB_Az = radius(dB_Az,angle3, angle2);
    drB_Az = radius_unty(dB_Az,angle3,angle2,dangle3,dangle2);
    rB_C = radius(dB_C,angle3, angle4);
    drB_C = radius_unty(dB_C,angle3,angle4,dangle3,dangle4);
    rA_Az = radius(dA_Az,angle1, angle2);
    drA_Az = radius_unty(dA_Az,angle1,angle2,dangle1,dangle2);
    rA_C = radius(dA_C,angle1, angle4);
    drA_C = radius_unty(dA_C,angle1,angle4,dangle1,dangle4);
    rC_Az = radius(dC_Az,angle4, angle2);
    drC_Az = radius_unty(dC_Az,angle4,angle2,dangle4,dangle2);
    //se declara vector con las medias de radio segun las mediciones en cada ciudad

    avgr[0]=rB_A, avgr[1]=rB_Az, avgr[2]=rB_C, avgr[3]=rA_Az, avgr[4]=rA_C, avgr[5]=rC_Az;
    avgdr[0]=drB_A, avgdr[1]=drB_Az, avgdr[2]=drB_C, avgdr[3]=drA_Az, avgdr[4]=drA_C, avgdr[5]=drC_Az;
    //estimacion final del radio de la tierra segun las medidas tomadas en distintas ciudades

    rf=average(avgr);
    drf=average(avgdr);

    std::cout << "\n" << "El radio terrestre, segun las medidas tomadas, es: "  << rf << " +/- " << drf << " metros" << "\n";

	avT1 = average(T1);
	avT2 = average(T2);
	avT3 = average(T3);
	avT4 = average(T4);

	gA = gravity(avl1,avT1);
	gAz = gravity(avl2,avT2);
	gB = gravity(avl3,avT3);
	gC = gravity(avl4,avT4);

    return 0;
}

//funcion de promedios
double average(length l)
{
    double sum = 0.0;
    for (auto &val : l){
        sum += val;
    }

    return sum/l.size();
}

//funcion de expansion de incertidumbre segun el error de medicion y el numero de datos tomados
double uncertainty (double ucty, int data)
{
    return data*ucty;
}

//calcula el angulo de incidencia en funcion de la altura de un objeto y el largo de su sombra
double angle (double s, double h)
{
    double rad;
    rad = atan(s/h);
    return (rad*180.0)/M_PI;
}
//calcula la incertidumbre segun el calculo del angulo de incidencia
double angle_unty (double s, double ds, double h, double dh)
{
    return (sqrt((h*ds)*(h*ds)+(s*dh)*(s*dh)))/(s*s+h*h);
}

//calcula el radio en funcion del angulo de incidencia y de la distancia (N-S) entre ciudades
double radius (double dist, double phi1, double phi2)
{
    return dist/std::abs(phi1-phi2);
}

double radius_unty (double d, double phi1, double phi2, double dphi1, double dphi2)
{
    return sqrt((d*d)/(pow(phi2-phi1,4))*(dphi1*dphi1+dphi2*dphi2)); //hay que ver que esto no bote problemas, porque pow trabaja con floats y le estoy metiendo doubles
}

double gravity(double length, double period)
{
	double g = 0.0;
	g = 4*M_PI*M_PI*((length)/(period*period));
	
	return g;
}

//double gravity_uncty(double length, double period, double dlength, double dperiod)
//{
	//return 0;
//}