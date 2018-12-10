//p2d_collision.h

class CP2D_Collision {
public:
	CP2D_Collision();
	~CP2D_Collision(){}

	void Add(CP2D_Body* a,CP2D_Body * b){body_a.push_back(a);body_b.push_back(b);}
	void Clear(){body_a.clear();body_b.clear();}
	void Check(std::vector<CP2D_Body*>);
	void Resolve();

	std::vector<CP2D_Body*>body_a;
	std::vector<CP2D_Body*>body_b;
};
CP2D_Collision::CP2D_Collision(){}

void CP2D_Collision::Check(std::vector<CP2D_Body*>body){
	for(unsigned int i=0;i<body.size();i++){
		for(unsigned int j=0; j<i; j++){
			if(body[i]->id != body[j]->id){
				if(body[i]->Check_Collision(body[j]) && (body[i]->solid && body[j]->solid)){
					Add(body[i],body[j]);
					//body[i]->collision=true;
					//body[j]->collision=true;
				}
			}
		}
	}
}
void CP2D_Collision::Resolve(){
	for(unsigned int i=0;i<body_a.size();i++){
		float x1 = body_a[i]->position.x;
		float y1 = body_a[i]->position.y;
		float r1 = body_a[i]->radius;
	
		float x2 = body_b[i]->position.x;
		float y2 = body_b[i]->position.y;
		float r2 = body_b[i]->radius;
		float distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
		float overlap_distance = 0.5 * (distance - r1 - r2);

		body_a[i]->position.x += overlap_distance * (body_a[i]->position.x - body_b[i]->position.x) / distance;
		body_a[i]->position.y += overlap_distance * (body_a[i]->position.y - body_b[i]->position.y) / distance;

		body_b[i]->position.x -= overlap_distance * (body_b[i]->position.x - body_a[i]->position.x) / distance;
		body_b[i]->position.y -= overlap_distance * (body_b[i]->position.y - body_a[i]->position.y) / distance;

		float nx = (x2 - x1) / distance;
		float ny = (y2 - y1) / distance;

		float tx = -ny;
		float ty = nx;

		float dpTan1 = body_a[i]->velocity.x * tx + body_a[i]->velocity.y * ty;
		float dpTan2 = body_b[i]->velocity.x * tx + body_b[i]->velocity.y * ty;

		float dpNorm1 = body_a[i]->velocity.x * nx + body_a[i]->velocity.y * ny;
		float dpNorm2 = body_b[i]->velocity.x * nx + body_b[i]->velocity.y * ny;

		float m1 = (dpNorm1 * (body_a[i]->mass - body_b[i]->mass) + 2.0f * body_b[i]->mass * dpNorm2) / (body_a[i]->mass + body_b[i]->mass);
		float m2 = (dpNorm2 * (body_b[i]->mass - body_a[i]->mass) + 2.0f * body_a[i]->mass * dpNorm1) / (body_a[i]->mass + body_b[i]->mass);

		body_a[i]->velocity.x = tx * dpTan1 + nx * m1;
		body_a[i]->velocity.y = ty * dpTan1 + ny * m1;

		body_b[i]->velocity.x = tx * dpTan2 + nx * m2;
		body_b[i]->velocity.y = ty * dpTan2 + ny * m2;

		//printf("Collision Resolved\n");

		body_a[i]->collision=true;
		body_b[i]->collision=true;
	}
	if(!body_a.empty())Clear();
}