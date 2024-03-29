# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    
    switch(id){
      
        case 0:
            thinkPoda(*actual, c_piece,id_piece, dice, 0,menosinf,masinf);
            break;
    }

    
}

 void AIPlayer::thinkAleatorio(color & c_piece,  int & id_piece, int & dice) const{
     cout << "caso0" << endl;
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }

    /*
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
    */
 }

void AIPlayer::thinkAleatorioMasInteligente(color & c_piece,  int & id_piece, int & dice) const{
    cout << "caso1" << endl;
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    //En vez de elegir un dado al azar, miro primero cuales tienen fichas que se pueden mover.

    vector<int> current_dices_que_pueden_mover_ficha;
    for(int i=0; i<current_dices.size(); i++){

        //se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces=actual->getAvailablePieces(c_piece, current_dices[i]);

        //si se pueden mover fichas para el dado actual, lo añado al vector de dados que pueden mover fichas.
        if(current_pieces.size() > 0){
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }

    }
    //si no tengo ningún dado que pueda mover fichas, paso turno con un dado al azar (la macro skip_turn me permite no mover)
    if(current_dices_que_pueden_mover_ficha.size() == 0){
        dice = current_dices[rand() % current_dices.size()];
        id_piece = SKIP_TURN;
    } else {
        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];
    
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido
        current_pieces = actual->getAvailablePieces(c_piece, dice);

        //muevo una ficha al azar de entre las que se pueden mover
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    

    
    

}

void AIPlayer::thinkFichaMasAdelantada(color & c_piece,  int & id_piece, int & dice) const {
    cout << "caso2" << endl;
    //elijo el dado haciendo lo mismo que el jugador anterior.
    thinkAleatorioMasInteligente(c_piece, id_piece, dice);


    //obtengo el vector de fichas:
    vector<int> current_pieces = actual->getAvailablePieces(c_piece,dice);
    int id_ficha_mas_adelantada = -1;
    int min_distancia_meta = 9999;

    for(int i=0; i<current_pieces.size(); i++){

        int distancia_meta = actual->distanceToGoal(c_piece, current_pieces[i]);
        if(distancia_meta < min_distancia_meta){
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }

    }

    if(id_ficha_mas_adelantada == -1){
        id_piece = SKIP_TURN;
    } else {
        id_piece = id_ficha_mas_adelantada;
    }

}

void AIPlayer::thinkMejorOpcion(color & c_piece,  int & id_piece, int & dice) const{
    
    cout << "caso3" << endl;
    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);

    bool me_quedo_con_esta_accion = false;

    while(!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion){
        if(siguiente_hijo.isEatingMove() or siguiente_hijo.isGoalMove() or 
        (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador)){

            me_quedo_con_esta_accion = true;

        } else {
            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        }
    }


    if(me_quedo_con_esta_accion){
        c_piece = last_c_piece;
        id_piece = last_id_piece;
        dice = last_dice;
    } else {
        thinkFichaMasAdelantada(c_piece, id_piece, dice);
    }

}

int AIPlayer::thinkMiniMax(color & c_piece,  int & id_piece, int & dice, int prof, bool esMax ) const{
    if(prof == 0) cout << "Claculando Plan" << endl;

    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;
    
    double value;

    if(prof == 4){
        return ValoracionTest(*actual, c_piece);
    }

    if(esMax) //es Max
        value = menosinf;   
     else  //es Min
        value = masinf;
        
        Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        while(!(siguiente_hijo == *actual)){
            if(!siguiente_hijo.isEatingMove()) esMax = !esMax;
            
            int n = thinkMiniMax(last_c_piece, last_id_piece, last_dice, prof + 1,esMax);

            if((n < value and !esMax) or (n>value and esMax)) value = n;

            if(prof == 0){
                c_piece = last_c_piece;
                id_piece = last_id_piece;
                dice = last_dice;
            }

            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        }
        return value;

}



//---------------- Heurísticas -----------------------------------------------



/*
NOTAS: hacer alguna forma de mantener las barreras, si estoy en lamisma casilla que alguien, esperar a que se mueva para coemrmelo después
no comerme fichas mías si tengo 3 en la meta y que se deje comer por el que tiene 3 fichas en la meta. para así no autosabotearme.

NO PONERSE DELANTE DE ALGUIEN QUE ESTE EN UNA CASILLA SEGURA

*/
double AIPlayer::Heu1(const Parchis &estado, int jugador){
    
    //si la casilla es fina queue le doy 5 puntos.
    int oponente = (jugador + 1) % 2;
    double puntuacionJugador = 0;
    double puntuacion_oponente = 0;
    
    const double CASILLA_NORMAL = 70;
    const double CASILLA_SEGURA = 8;
    const double ENTRADA_META = 2;
    const double BARRERA = 0;
    const double COMER = 20;

    if(estado.getWinner() == jugador)
        return masinf;
     else if (estado.getWinner() == oponente)
        return menosinf;
    

    if(estado.isEatingMove() ){
        if(estado.getCurrentPlayerId() == jugador)
            puntuacionJugador += COMER;
        else
            puntuacion_oponente += COMER;

    }
    
//--------------- YO ---------------------
    vector<color> my_colors = estado.getPlayerColors(jugador);
    for (int i = 0; i < my_colors.size(); i++){
        color c = my_colors[i];
        puntuacionJugador += estado.piecesAtGoal(c) *12;
        for (int j = 0; j < num_pieces; j++){

            if(estado.getBoard().getPiece(c,j).type == final_queue)
                puntuacionJugador += 5;

            if(estado.getBoard().getPiece(c,j).type != home)
                puntuacionJugador += 7;
            
            
            if(estado.isWall(estado.getBoard().getPiece(c,j)))
                puntuacionJugador += BARRERA;
                
            if(estado.getBoard().getPiece(c,j).type == normal)
                puntuacionJugador += CASILLA_NORMAL - estado.distanceToGoal(c,j);

            //Sumo puntuación si está en un lugar seguro.
            if (estado.isSafePiece(c, j))
                    puntuacionJugador += CASILLA_SEGURA;
            else if (estado.getBoard().getPiece(c, j).type == goal)
                    puntuacionJugador += ENTRADA_META;
            }
    
        }


//----------------OPONENTE -----------------------------
        vector<color> op_colors = estado.getPlayerColors(oponente);
        for (int i = 0; i < op_colors.size(); i++){
            color c = op_colors[i];
           puntuacion_oponente += estado.piecesAtGoal(c) *12;


            for (int j = 0; j < num_pieces; j++){

                if(estado.getBoard().getPiece(c,j).type == final_queue)
                puntuacionJugador += 5;

                if(estado.getBoard().getPiece(c,j).type != home)
                puntuacion_oponente += 7;
                

                if(estado.isWall(estado.getBoard().getPiece(c,j)))
                    puntuacion_oponente += BARRERA;
                
                if(estado.getBoard().getPiece(c,j).type == normal)
                    puntuacion_oponente += CASILLA_NORMAL - estado.distanceToGoal(c,j);

                if (estado.isSafePiece(c, j))
                    puntuacion_oponente += CASILLA_SEGURA;
                else if (estado.getBoard().getPiece(c, j).type == goal)
                    puntuacion_oponente += ENTRADA_META;
                
            }
        }


    return puntuacionJugador - puntuacion_oponente;
}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::thinkPoda(const Parchis &actual, color & c_piece,  int & id_piece, int & dice, int prof, double a, double b) const{
   
    if(prof == 6 || actual.gameOver()) return Heu1(actual, this->actual->getCurrentPlayerId());

    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;
    bool esMax,poda = false;
    double Valor_Hijo;
    if(prof == 0 ) id_piece = -1;
    esMax = (actual.getCurrentPlayerId() == this->actual->getCurrentPlayerId());
    
    Parchis siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);

    while(!(siguiente_hijo == actual) and !poda){
      
       

        Valor_Hijo = thinkPoda(siguiente_hijo, last_c_piece, last_id_piece, last_dice, prof + 1,a,b);
    
        if(esMax and (a < Valor_Hijo)){
            a = Valor_Hijo;
            
            if(prof == 0){
                        c_piece = last_c_piece;
                        id_piece = last_id_piece;
                        dice = last_dice;
                        cout << "prof: " << prof << " id_piece: " << id_piece << " cpiece: " << c_piece << "dice: " <<dice << endl;
            }
        } else if(!esMax and(b > Valor_Hijo)) 
            b = Valor_Hijo;

        if(b <= a) 
            poda = true;
        else 
            siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);
    }

    

    if(id_piece == -1 and prof == 0){
        
        thinkAleatorio(c_piece, id_piece, dice);
        
    }
    
    return (esMax) ? a : b;
}
