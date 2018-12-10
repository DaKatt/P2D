//p2d_engine.h

class CP2D_Engine {
public:
	CP2D_Engine();
	~CP2D_Engine(){}

	CP2D_Body * Create_Body(float xpos,float ypos,float radius_size,float mass_size);
	void Add_Body(CP2D_Body*);
	void Draw();
	void Update();
	void Remove();

	std::vector<CP2D_Body*>my_body;
	std::vector<CP2D_Body*>::iterator iter;
	CP2D_Collision * my_collision;
};
CP2D_Engine::CP2D_Engine(){
	/*
	Add_Body(Create_Body(300,100,20,1));
	Add_Body(Create_Body(300,400,100,1));
	Add_Body(Create_Body(700,700,150,1));

	
	my_body[0]->velocity.Set(0.1f,1.0f);
	my_body[1]->velocity.Set(-0.1f,-1.0f);
	my_body[2]->velocity.Set(-2.5f,-2.0f);
	*/
	my_collision = new CP2D_Collision();
}
CP2D_Body * CP2D_Engine::Create_Body(float xpos,float ypos,float radius_size,float mass_size){
	CP2D_Body * b = new CP2D_Body(xpos,ypos,radius_size,mass_size);
	return b;
}
void CP2D_Engine::Add_Body(CP2D_Body * b){
	my_body.push_back(b);
}
void CP2D_Engine::Draw(){
	for(unsigned int i=0;i<my_body.size();i++){
		my_body[i]->Draw();
	}
}
void CP2D_Engine::Update(){
	
	for(unsigned int i=0;i<my_body.size();i++){
		my_body[i]->Update();
	}

	my_collision->Check(my_body);
	my_collision->Resolve();

	Remove();
}
void CP2D_Engine::Remove(){
	for(iter = my_body.begin(); iter != my_body.end(); iter++){
		if((*iter)->dead){
			my_body.erase(iter);
			break;
		}
	}
}
CP2D_Engine * p2d_engine;