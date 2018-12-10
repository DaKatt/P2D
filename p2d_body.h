//p2d_body.h

class CP2D_Body {
public:
	CP2D_Body();
	CP2D_Body(float xpos,float ypos,float radius_size,float mass_size);
	~CP2D_Body(){}

	void Setup(float xpos,float ypos,float radius_size,float mass_size);
	void Draw();
	void Update();
	void Update_Position();
	bool Check_Collision(CP2D_Body*);

	CP2D_Vector position;
	CP2D_Vector velocity;
	CP2D_Vector acceleration;
	float mass;
	float radius;
	int id;
	bool collision;
	bool hide;
	bool solid;
	bool dead;

	static int new_UID;
};
CP2D_Body::CP2D_Body() : id(new_UID++){}
CP2D_Body::CP2D_Body(float xpos,float ypos,float radius_size,float mass_size) : id(new_UID++){
	position.x = xpos;
	position.y = ypos;
	radius = radius_size;
	mass = mass_size;
	collision = false;

	velocity.Set(0.0f,0.0f);
	acceleration.Set(0.0f,0.0f);

	//printf("CP2D_Body %i Created\n",id);

	hide = false;
	solid = true;
	dead = false;
}
void CP2D_Body::Setup(float xpos,float ypos,float radius_size,float mass_size){}

void CP2D_Body::Draw(){
	if(!hide)al_draw_circle(position.x,position.y,radius,al_map_rgb(255,255,255),1);
}
void CP2D_Body::Update(){
	Update_Position();
}
void CP2D_Body::Update_Position(){
	velocity.Add(acceleration);
	position.Add(velocity);

	acceleration.Clear();
}
bool CP2D_Body::Check_Collision(CP2D_Body * other_circle){
	if(solid==true && other_circle->solid==true){
		float x1 = position.x;
		float y1 = position.y;
		float r1 = radius;
	
		float x2 = other_circle->position.x;
		float y2 = other_circle->position.y;
		float r2 = other_circle->radius;

		float distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
		float radii = r1+r2;


		if(fabs(distance)<radii){
			collision = true;
			return true;
		} else {
			collision=false;
			return false;
		}
	}
	return false;

}
int CP2D_Body::new_UID = 0;