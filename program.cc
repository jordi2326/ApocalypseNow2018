#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */

#define PLAYER_NAME JordiDEF1


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  static constexpr int I[8] = { 1, 1, 0, -1, -1, -1,  0,  1 };
  static constexpr int J[8] = { 0, 1, 1,  1,  0, -1, -1, -1 };

  typedef vector<int> VE;
  

void bfs1(int id ){
	    Data in = data(id);
	int i = in.pos.i;
    int j = in.pos.j;
    int player = in.player;
    for (int k = 0; k < 8; ++k) {
      int ii = i + I[k];
      int jj = j + J[k];
      if (ii >= 0 and ii < MAX and jj >= 0 and jj < MAX) {
        int id2 = which_soldier(ii, jj);
        // If there is an enemy next to us, we attack.
        if (id2 and data(id2).player != player) {
          command_soldier(id, ii, jj);
          return;
        }
      }
    }
	 
			Position cd ;
			bool atac = false;
		  vector <vector <int> > W(60,vector<int>(60,-1));
		   vector <vector <bool> > visitados(60,vector<bool>(60,false));
		 
		   
		  Position p = in.pos;
		 
		  
		  visitados[i][j]= true ; 
		  queue<Position>q;
		  q.push(p);
		  W[i][j]=0;
		 
		  while ( not q.empty()  ){
			  Position z = q.front();
			  q.pop();
			  for(int k = 0 ; k < 8 ; ++k ) {
				  int ii = z.i + I[k];
				  int jj = z.j +J[k];
				  if (pos_ok(ii,jj) and not visitados[ii][jj] and movimiento_permitido(id,ii,jj) and which_soldier(ii,jj)== 0){
					  visitados[ii][jj]= true ;
					  W[ii][jj] = W[z.i][z.j]+1;
					  if (post_owner(ii,jj ) != player and post_owner(ii,jj) != -2 ){
						  cd.i = ii ;
						  cd.j = jj;
						  move(cd,W,id);
						  return;
					  }
					  Position nova;
					  nova.i=ii;
					  nova.j=jj;
					  q.push(nova);
					  
				  
			  }
		   

} 
}
}


    


    void move (Position c , vector <vector <int> > W , int id){

		Position aux;
	while (W[c.i][c.j]  !=0) {
	  for (int k = 0; k < 8; ++k) {
	    aux.i = c.i - I[k];
	    aux.j = c.j - J[k];
	    if (W[aux.i][aux.j] == (W[c.i][c.j])-1) c = aux;
	   if (W[c.i][c.j] == 0) {
			 Data in = data(id);
			int i = in.pos.i;
			int j = in.pos.j;
			 int ii = i + I[k];
			int jj = j + J[k];
	     	command_soldier(id ,ii , jj  );
			return ;
	 
	    }
	  }
	}
}
  
  
  bool movimiento_permitido(int id, int x, int y) {

    if (what(x,y) == WATER or what(x,y) == MOUNTAIN) return false;
    if (fire_time(x,y) != 0) return false;
    return true;

}
	bool cantidad_jugadores (int x , int y , int id ){
			int rivales , mios ; 
			rivales = mios = 0 ;
				   vector <vector <int> > visitados(60,vector<int>(60,0));
			for(int i = 0 ; i < 60 ; ++i ) {
				for (int j = 0 ; j < 60 ; ++j ) {
					if (which_soldier(i,j) != id ) visitados[i][j]= 1 ;
				}
			}
			for (int i = -2 ; i <=  2 ; ++i ){
					if ( visitados[x+1][y+i]==1) ++rivales;
					else if (visitados[x+1][y+i]==0)++mios;
					if ( visitados[x-1][y+i] ==1) ++rivales ; 
					else if (visitados[x-1][y+i]== 0) ++ mios;	
					if ( visitados[x+i][y+1] == 1 ) ++rivales ;
					else if (visitados[x+i][y+1]== 0) ++mios ;
					if ( visitados[x+i][y-1] == 1 ) ++rivales ;
					else if (visitados[x+i][y-1] == 0 ) ++mios; 
					 visitados[x+1][y+i]=visitados[x-1][y+i]=visitados[x+i][y+1]=visitados[x+i][y-1] = -1;
}

				


	 if ( rivales >= 1  or  mios < rivales  ) return true ; 
	 else return false ; 
	
  
}


  void play_helicopter(int id) {
	    Data in = data(id);
	int i = in.pos.i;
    int j = in.pos.j;
	 int player = in.player;
	
  
		//if (data(id).napalm == 0 and cantidad_jugadores(i , j , player)) {
      //command_helicopter(id, NAPALM);
      //return;
    //}
    // With probability 20% we turn counter clockwise,
    // otherwise we try to move forward two steps.
    Position p = data(id).pos;
    int dir = data(id).orientation;
    if (round() == 1 ){
    command_helicopter(id,  CLOCKWISE );
    return ;
}
    else {
	if (  dir == 0 ){
			if (pos_ok(i+4,j)  or( which_helicopter(i+4 , j )== 0 and pos_ok(i+4,j) )   or ( what(i+4 , j )!= MOUNTAIN and pos_ok(i+4,j)  ) )command_helicopter(id,  FORWARD2 );
				else if (which_helicopter(i+4 , j ) != 0 and pos_ok(i+4,j))command_helicopter(id , COUNTER_CLOCKWISE);
				else command_helicopter(id ,CLOCKWISE);
				return;
  }

	else if ( dir == 1  ){
			if (not pos_ok(i ,j+4 ) or( what(i, j+4)==MOUNTAIN and pos_ok(i ,j+4 ))  )command_helicopter(id,  CLOCKWISE );
				else if (which_helicopter(i , j+4 ) != 0 and pos_ok(i,j+4))command_helicopter(id , COUNTER_CLOCKWISE);
				else command_helicopter(id , FORWARD2);
				return ;
	

}
	else if ( dir == 2  ){
			if (pos_ok(i-4,j )  or( which_helicopter(i-4,j)== 0 and pos_ok(i-4,j )) )command_helicopter(id,  FORWARD2 );
				else if (which_helicopter(i-4 , j ) != 0 and pos_ok(i-4,j))command_helicopter(id , COUNTER_CLOCKWISE);
				else command_helicopter(id ,CLOCKWISE);
				return ;
  }


	else {
			if (not pos_ok(i,j-4 ) or (what(i, j-4)==MOUNTAIN and pos_ok(i,j-4 )) )  command_helicopter(id,  CLOCKWISE );
				else if (which_helicopter(i , j-4 ) != 0 and pos_ok(i,j-4))command_helicopter(id , COUNTER_CLOCKWISE);
				else command_helicopter(id , FORWARD2);
				return ;
			}
		
	}	
}
  void throw_parachuter(int helicopter_id) {
    // We get the data of the helicopter...
    Data in = data(helicopter_id);
    // ... and try to throw a parachuter, without even examining the land.
    int ii = in.pos.i + random(-2, 2);
    int jj = in.pos.j + random(-2, 2);
    if (ii >= 0 and ii < MAX and jj >= 0 and jj < MAX )
      command_parachuter(ii, jj);
  }
  
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

    int player = me();
    VE H = helicopters(player); // helicopters of my player
    VE S =    soldiers(player); //    soldiers of my player

    // If in a random helicopter I have parachuters, I throw one.
    int helicopter_id = H[random(0, H.size()-1)];
    if (not data(helicopter_id).parachuters.empty()) throw_parachuter(helicopter_id);

    for (int i = 0; i < (int)H.size(); ++i) play_helicopter(H[i]);
    for (int i = 0; i < (int)S.size(); ++i) bfs1( S[i]);
  }

};

constexpr int PLAYER_NAME::I[8];
constexpr int PLAYER_NAME::J[8];

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
