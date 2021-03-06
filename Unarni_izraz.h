#pragma once
#include "Tipovi_podataka.h"
#include "class_definitions_Izrazi.h"
#include "class_definitions_Naredbena_struktura.h"
#include "class_definitions_Deklaracije_i_definicije.h"
#include "produkcije.h"
#include <math.h>

povratni_tip Unarni_izraz::produkcija(Node produkcija, Tablica_djelokruga &tablica, std::string ntip)
{
    cerr << "Unarni_izraz" << endl;
	povratni_tip xy;
	
	//produkcija 1
	if(produkcija.nodes.size() == 1
    && produkcija.nodes[0].znak == "<postfiks_izraz>")
       xy = Unarni_izraz::produkcija1(produkcija, tablica, ntip);
    //produkcija 2
    else if(produkcija.nodes.size() == 2
         && produkcija.nodes[0].znak.substr(0, produkcija.nodes[0].znak.find(" ")) == "OP_INC"
         && produkcija.nodes[1].znak == "<unarni_izraz>")
       xy = Unarni_izraz::produkcija2(produkcija, tablica, ntip);
    //produkcija 3
    else if(produkcija.nodes.size() == 2
         && produkcija.nodes[0].znak.substr(0, produkcija.nodes[0].znak.find(" ")) == "OP_DEC"
         && produkcija.nodes[1].znak == "<unarni_izraz>")
       xy = Unarni_izraz::produkcija3(produkcija, tablica, ntip);
    //produkcija 4
    else if(produkcija.nodes.size() == 2
         && produkcija.nodes[0].znak == "<unarni_operator>"
         && produkcija.nodes[1].znak == "<cast_izraz>")
       xy = Unarni_izraz::produkcija4(produkcija, tablica, ntip);

	return xy; //nasumična varijabla xy je tu samo radi točnosti kompaliranja (zamjeni je s potrebnim vrijednostima)
}

povratni_tip Unarni_izraz::produkcija1(Node produkcija, Tablica_djelokruga &tablica, std::string ntip)
{
	povratni_tip xy;
	Postfiks_izraz postfiks_izraz;
	
	//1
	xy = postfiks_izraz.produkcija(produkcija.nodes[0], tablica, ntip);
	
	return xy;
}

povratni_tip Unarni_izraz::produkcija2(Node produkcija, Tablica_djelokruga &tablica, std::string ntip)
{
	povratni_tip xy;
	
	//1
	xy = Unarni_izraz::produkcija(produkcija.nodes[1], tablica, ntip);
    //2
    xy.tip = "int";
    xy.l_izraz = false;
	
	return xy;
}

povratni_tip Unarni_izraz::produkcija3(Node produkcija, Tablica_djelokruga &tablica, std::string ntip)
{
	povratni_tip xy;
	
	//1
	xy = Unarni_izraz::produkcija(produkcija.nodes[1], tablica, ntip);
    //2
    xy.tip = "int";
    xy.l_izraz = false;
    
	return xy;
}

povratni_tip Unarni_izraz::produkcija4(Node produkcija, Tablica_djelokruga &tablica, std::string ntip)
{
	povratni_tip xy;
	Cast_izraz cast_izraz;
	povratni_tip oper;
	Unarni_operator unarni_operator;
	
    //1
	xy = cast_izraz.produkcija(produkcija.nodes[1], tablica, ntip);
    //2
    xy.tip = "int";
    xy.l_izraz = false;
    
    //LABOS 4
	oper = unarni_operator.produkcija(produkcija.nodes[0], tablica, ntip);
	if(oper.ime_varijable == "MINUS")
	{
       string temp = xy.ime_varijable.substr(xy.ime_varijable.find_last_of("_")+1);
       int indeks = atoi(temp.c_str());
       indeks = abs(indeks);
       indeks--;
       if(konstante[indeks][0] == '-')
          konstante[indeks] = konstante[indeks].substr(1);
       else
          konstante[indeks] = "-" + konstante[indeks];
    }
    else if(oper.ime_varijable == "OP_TILDA")
    {
       string temp = xy.ime_varijable.substr(xy.ime_varijable.find_last_of("_")+1);
       int indeks = atoi(temp.c_str());
       indeks = abs(indeks);
       indeks--;
       int a = atoi(konstante[indeks].c_str());
       a = ~a;
       char nesto[50];
       sprintf(nesto, "%d\0", a);
       string novi_string(nesto);
       konstante[indeks] = novi_string;
    }
    else if(oper.ime_varijable == "OP_NEG")
    {
       string temp = xy.ime_varijable.substr(xy.ime_varijable.find_last_of("_")+1);
       int indeks = atoi(temp.c_str());
       indeks = abs(indeks);
       indeks--;
       int a = atoi(konstante[indeks].c_str());
       a = !a;
       char nesto[50];
       sprintf(nesto, "%d\0", a);
       string novi_string(nesto);
       konstante[indeks] = novi_string;
    }
	
	return xy;
}
