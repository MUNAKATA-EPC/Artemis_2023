int IR_Pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
VectorFloat Ball_pos;

int Ball_theta, Ball_radius;

void IRRing_setup(){
    for(int i = 0; i < 16; i++)
    { 
        pinMode(i, INPUT);
    }
}

void IRRing_loop(){
    //Culc IR Sensor's vectors
    for(int i = 0; i < 16; i++)
    { 
        //interval of degree of each IR Sensors
        int interval = 360 / i;
        Ball_pos.x += sin(radians(interval + (interval / 2))) * analogRead(IR_Pins[i]);
        Ball_pos.y += cos(radians(interval + (interval / 2))) * analogRead(IR_Pins[i]);
    }
    
    //Culc theta and radius between robots and ball
    Ball_theta = degrees(atan2(Ball_pos.x, Ball_pos.y));
    Ball_radius = sqrt(pow(Ball_pos.x, 2.0) + pow(Ball_pos.y, 2.0));
}