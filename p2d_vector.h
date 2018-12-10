//p2d_vector.h

class CP2D_Vector {
public:
	CP2D_Vector();
	~CP2D_Vector(){}

	void Add(float a){x+=a;y+=a;}
	void Add(float a1,float a2){x+=a1;y+=a2;}
	void Add(CP2D_Vector vec){x+=vec.x;y+=vec.y;}

	void Sub(float a){x-=a;y-=a;}
	void Sub(float a1,float a2){x-=a1;y-=a2;}
	void Sub(CP2D_Vector vec){x-=vec.x;y-=vec.y;}

	void Mul(float a){x*=a;y*=a;}
	void Mul(float a1,float a2){x*=a1;y*=a2;}
	void Mul(CP2D_Vector vec){x*=vec.x;y*=vec.y;}

	void Div(float a){x/=a;y/=a;}
	void Div(float a1,float a2){x/=a1;y/=a2;}
	void Div(CP2D_Vector vec){x/=vec.x;y/=vec.y;}

	void Set(float a1,float a2){x=a1;y=a2;}
	void Clear(){x=0.0f;y=0.0f;w=1.0f;}

	float Length();
	CP2D_Vector Normalize();
	float Dot(CP2D_Vector);

	float x,y,w;
};
CP2D_Vector::CP2D_Vector(){}

float CP2D_Vector::Length(){
	return sqrt(x*x+y*y);
}
CP2D_Vector CP2D_Vector::Normalize(){
	CP2D_Vector temp_vec;
	float l = this->Length();
	if(l!=0){
		temp_vec.x = x/l;
		temp_vec.y = y/l;
	}
	return temp_vec;
}
float CP2D_Vector::Dot(CP2D_Vector vec){
	return (x*vec.x +y*vec.y);
}