#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    

    
    
    //set map
    heightMap.load("crater_depth.jpg");
    textureMap.load("crater_texture.jpg");
    generateTerrain();
    
    
    
    //setLight
    //light.setDirectional();
    //light.setDiffuseColor(ofColor::white);
    sun_angle = 0;

    //light.rotateDeg(200,0,1,0);
 

    
    //set star
    ofMesh sphere = ofMesh::sphere(5000,250);
    for(int i=0;i<sphere.getVertices().size();i++){
        if(ofRandom(0,15)<1){
            starfield.addVertex(sphere.getVertices()[i]);
        }
    }
    
    help = false;
    change_terrain = false;
    type = 1;
    
    //set player wolf

    Wolf WOLF = Wolf(1);
    wolfs.push_back(WOLF);
    
    change_terrain_direction = 1;

  
    wolf_born = ofGetElapsedTimef();
    sheep_born = ofGetElapsedTimef();
    
    
    //gui setup
    Wolf_Parameter.setName("Wolf");
    Wolf_Parameter.add(Wolf_number.set("Number",1,0,50));
    Wolf_Parameter.add(Wolf_born_rate.set("born_rate",10,5,15));
    Wolf_Parameter.add(Wolf_hunt_rate.set("hunt_rate",10,5,15));
    Wolf_Parameter.add(Wolf_death_rate.set("death_rate",30,20,40));
    
    Sheep_Parameter.setName("Sheep");
    Sheep_Parameter.add(Sheep_number.set("Number",1,0,50));
    Sheep_Parameter.add(Sheep_born_rate.set("born_rate",10,5,15));
    Sheep_Parameter.add(Sheep_death_rate.set("death_rate",30,20,40));
    
    
    Begin_Parameter.setName("Preference");
    Begin_Parameter.add(BEGIN.set("begin",false));
   

    gui.setup();
    gui.add(Wolf_Parameter);
    gui.add(Sheep_Parameter);
    gui.add(BEGIN);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(creater){

        cam.setPosition(0, 4000, 0);
        cam.lookAt(glm::vec3(0,-1,0));
        cam.rotate(-10,cam.getUpAxis());
        

        if(creater){
            if(change_terrain){
                glm::vec2 pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
                terrain_changer(pos);
            }
        }
        
    }
    
    

    update_gui();
    
    time = ofGetElapsedTimef();
    
    

    //move light;
    sun_angle += 0.005;
    light_pos = glm::vec3(4096*cos(sun_angle),4096*sin(sun_angle),0);
    light.setPosition(light_pos);
    
    
    
    if(BEGIN){
        
        while(wolfs.size()<Wolf_number){
            glm::vec2 pos_xz = glm::vec2(ofRandom(-2048,2048),ofRandom(-2048,2048));
            glm::vec3 pos = glm::vec3(pos_xz.x,terrain.getheight(pos_xz),pos_xz.y);
            Wolf WOLF = Wolf(pos);
            wolfs.push_back(WOLF);
        }
        
        while(wolfs.size()>Wolf_number){
            wolfs.pop_back();
        }
        
        while(sheeps.size()<Sheep_number){
            glm::vec2 pos_xz = glm::vec2(ofRandom(-2048,2048),ofRandom(-2048,2048));
            glm::vec3 pos = glm::vec3(pos_xz.x,terrain.getheight(pos_xz),pos_xz.y);
            Sheep SHEEP = Sheep(pos);
            sheeps.push_back(SHEEP);
        }
        
        while(sheeps.size()>Sheep_number){
            sheeps.pop_back();
        }
        
        
        
        if(ofGetElapsedTimef() - wolf_born > (Wolf_born_rate+ofRandom(-2,2))){
            WOLF_born();
            wolf_born = ofGetElapsedTimef();
        }
        
        if(ofGetElapsedTimef() - sheep_born > (Sheep_born_rate+ofRandom(-2,2))){
            SHEEP_born();
            sheep_born = ofGetElapsedTimef();
        }
        
        //simulate hunting;
        wolf_hunting();
        check_hunting();
        
        //update wolf;
        for(int i=0;i<wolfs.size();i++){
        
            move_wolf(wolfs[i]);
            
            wolfs[i].update();
        }
        
        
        //update sheep;
        for(int j=0;j<sheeps.size();j++){
            move_sheep(sheeps[j]);
            sheeps[j].update();
        }
        
        died();
        

        Wolf_number = wolfs.size();
        Sheep_number = sheeps.size();
        //died wolf and sheep;
       
        
    }

     
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofSetColor(255);
    
    stringstream text;
    
    ofPushStyle();
    
    if(!help && !creater){
        text << "type h for help\n";
        text << "type c to change the terrain\n";
        text << "type r to restart\n";
    }
    if(help && !creater){
        text << "born_rate change the frequency of new birth for wolfs and sheeps\n";
        text << "death_rate change the frequency of death for wolfs and sheeps\n";
        text << "hunt_rate change the frequency of hunting for the wolfs\n";
        text << "your goal is to change the parameter to get a stable ecosystem\n";
        text << "you can control the wolf with red shpere and the parameter is on the right\nuse wasd and " " to control the movement";
    }
    if(creater){
        ofSetColor(0);
        text << "click mouse to change the terrain, the large gap will prevent passing\n";
        text << "use o to change the direction of the changing\n";
        text << "use l to change the type of changing";
    }

    ofDrawBitmapStringHighlight(text.str(), ofGetWidth()/2-250, 20);
    

    
    
    ofPopStyle();
    string player_hungry;
    float hp;
    
    player_hungry = "die";
    hp = 0;
    for(int i=0;i<wolfs.size();i++){
        if(wolfs[i].category == 1){
            if(wolfs[i].is_hungry){
                player_hungry = "yes";
                hp = ofGetElapsedTimef() - wolfs[i].hunt;
                hp = ofMap(hp, 0, 30, 100, 0);
            }else{
                player_hungry = "no";
                hp = 100;
            }
        }
    }
    
    glm::vec2 mouse = glm::vec2(ofGetMouseX(),ofGetMouseY());
    float le = glm::length(mouse-glm::vec2(ofGetWidth()/2,ofGetHeight()/2));
    
    ofDrawBitmapString("hungry: "+player_hungry, ofGetWidth()-150, 20);
    ofDrawBitmapString("hp: "+ofToString(hp ), ofGetWidth()-150, 40);




    cam.begin();
    light.enable();
    ofEnableDepthTest();
    ofEnableLighting();

    //draw the map
    ofRotateDeg(80, 0, 1, 0);
    textureMap.bind();
    terrain.draw();
    textureMap.unbind();
    ofSetColor(ofColor::white);

    
    //draw starfield
    ofPushStyle();
    ofSetColor(ofColor(255));
    starfield.drawVertices();
    ofPopStyle();
    


    //draw wolf
    for(int i=0;i<wolfs.size();i++){
        wolfs[i].draw();
    }
    
    
    //draw sheep
    for(int j=0;j<sheeps.size();j++){
        sheeps[j].draw();
    }
    
    light.disable();
    ofDisableLighting();
    ofDisableDepthTest();
    cam.end();
    
    gui.draw();
    
}

//generate the terrain
void ofApp::generateTerrain() {
    terrain = Terrain(4096,4096, 1024,1024);
    terrain.applyHeightMap(heightMap, -250, 250);
    terrain.mapTexture(textureMap.getTexture());
    terrain.setNormalsDrawLength(5);
    terrain.setPosition(0, -250, 0);
    
}

//move_wolf
void ofApp::move_wolf(Wolf& wolf){
    glm::vec2 pos_xz = glm::vec2(wolf.pos.x,wolf.pos.z);
    glm::vec2 new_pos = pos_xz + wolf.vel_xz;
    
    
    if(abs(terrain.getheight(pos_xz-new_pos))>300){
        wolf.vel_xz = -wolf.vel_xz;
    }else{
        //move face direction
        float Angle = atan2(wolf.vel_xz.y-0, wolf.vel_xz.x-0);
        Angle = ofMap(Angle, -PI, PI, -180, 180);
        wolf.face_angle = Angle;

        //move 3d position
        float height = terrain.getheight(new_pos);
        wolf.pos.x = new_pos.x;
        wolf.pos.y = height-225;
        wolf.pos.z = new_pos.y;
    }
    

}




//move_sheep
void ofApp::move_sheep(Sheep& sheep){
    glm::vec2 pos_xz = glm::vec2(sheep.pos.x,sheep.pos.z);
    glm::vec2 new_pos = pos_xz + sheep.vel_xz;
    
    if(abs(terrain.getheight(pos_xz-new_pos))>300){
        sheep.vel_xz = -sheep.vel_xz;
    }else{
        //move face direction
        float Angle = atan2(sheep.vel_xz.y-0, sheep.vel_xz.x-0);
        Angle = ofMap(Angle, -PI, PI, -180, 180);
        sheep.face_angle = Angle;

        //move 3d position
        float height = terrain.getheight(new_pos);
        sheep.pos.x = new_pos.x;
        sheep.pos.y = height-225;
        sheep.pos.z = new_pos.y;
    }
}



void ofApp::died(){
    vector<Wolf> tmp1;
    vector<Sheep> tmp2;
    for(int i=0;i<wolfs.size();i++){
        if(wolfs[i].over == false){
            tmp1.push_back(wolfs[i]);
        }
    }
    
    for(int j=0;j<sheeps.size();j++){
        if(sheeps[j].over == false){
            tmp2.push_back(sheeps[j]);
        }
    }
    wolfs.swap(tmp1);
    sheeps.swap(tmp2);

}


void ofApp::WOLF_born(){
    if(wolfs.size() != 0){
        int birth = 0;
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].is_hungry == false){
                birth += 1;
            }
        }
        for(int i=0;i<birth;i++){
          
                glm::vec2 pos_xz = glm::vec2(ofRandom(-2048,2048),ofRandom(-2048,2048));
                glm::vec3 pos = glm::vec3(pos_xz.x,terrain.getheight(pos_xz),pos_xz.y);
                Wolf WOLF = Wolf(pos);
                wolfs.push_back(WOLF);
            
        }
    }
}

void ofApp::SHEEP_born(){
    if(sheeps.size() != 0){
        int birth = 1 + sheeps.size()/2;
        for(int j=0;j<birth;j++){
            if(ofRandom(1,20)<19){
                glm::vec2 pos_xz = glm::vec2(ofRandom(-2048,2048),ofRandom(-2048,2048));
                glm::vec3 pos = glm::vec3(pos_xz.x,terrain.getheight(pos_xz),pos_xz.y);
                Sheep SHEEP = Sheep(pos);
                sheeps.push_back(SHEEP);
            }
        }
    }
}


void ofApp::wolf_hunting(){
    for(int i=0;i<wolfs.size();i++){
        if(wolfs[i].is_hungry == true && sheeps.size()!=0 && wolfs[i].category == 0){
            
            float min = 100000;
            Sheep hunted;
            
            for(int j=0;j<sheeps.size();j++){
                
                glm::vec3 wolf_pos = wolfs[i].pos;
                glm::vec2 wolf_pos_xz = glm::vec2(wolf_pos.x,wolf_pos.z);
                glm::vec3 sheep_pos = sheeps[j].pos;
                glm::vec2 sheep_pos_xz = glm::vec2(sheep_pos.x,sheep_pos.z);
                glm::vec2 distance = sheep_pos_xz-wolf_pos_xz;
                
                float dis = glm::length(distance);
                
                if(dis< min){
                    min = dis;
                    hunted = sheeps[j];
                }
            }

            wolfs[i].vel_xz = glm::vec2(hunted.pos.x,hunted.pos.z) - glm::vec2(wolfs[i].pos.x,wolfs[i].pos.z);
            wolfs[i].vel_xz.x = wolfs[i].vel_xz.x/10;
            wolfs[i].vel_xz.y = wolfs[i].vel_xz.y/10;
        }
    }
}

void ofApp::check_hunting(){
    for(int i=0;i<wolfs.size();i++){
        for(int j=0;j<sheeps.size();j++){
            if(wolfs[i].is_hungry == true){
                if(abs(wolfs[i].pos.x - sheeps[j].pos.x) < 50  &&   abs(wolfs[i].pos.z - sheeps[j].pos.z) <50){
                    wolfs[i].is_hungry = false;
                    sheeps[j].died();
                }
            }
        }
    }
}


//update the parameter for wolf and sheep
void ofApp::update_gui(){
    for(int i=0;i<wolfs.size();i++){
        wolfs[i].HUNTING_RATE = Wolf_hunt_rate;
        wolfs[i].DEATH_RATE = Wolf_death_rate;
    }
    
    for(int j=0;j<sheeps.size();j++){
        sheeps[j].DEATH_RATE = Sheep_death_rate;
    }
    
}

void ofApp::terrain_changer(glm::vec2 mouse_pos){
    
    glm::vec2 map_pos;
    map_pos.y = ofMap(ofGetMouseX()-ofGetWidth()/2, -323, 323, -2048, 2048);
    map_pos.x = ofMap(ofGetHeight()/2 - ofGetMouseY(), -323,323,-2048,2048);


    terrain.terrain_changer(map_pos, change_terrain_direction,type);

    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        wolfs.clear();
        sheeps.clear();
        terrain.clearParent();
        Wolf WOLF = Wolf(1);
        wolfs.push_back(WOLF);
        heightMap.load("crater_depth.jpg");
        textureMap.load("crater_texture.jpg");
        generateTerrain();
    }
    if(key == 'h'){
        help = !help;
    }
    if(key == 'w'){
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].category == 1){
                wolfs[i].vel_xz.x += 2;
            }
        }
    }
    if(key == 's'){
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].category == 1){
                wolfs[i].vel_xz.x -= 2;
            }
        }
    }
    if(key == 'a'){
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].category == 1){
                wolfs[i].vel_xz.y -= 2;
            }
        }
    }
    if(key == 'd'){
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].category == 1){
                wolfs[i].vel_xz.y += 2;
            }
        }
    }
    
    if(key == ' '){
        for(int i=0;i<wolfs.size();i++){
            if(wolfs[i].category == 1){
                wolfs[i].vel_xz = glm::vec2(0,0);
            }
        }
    }
    if(key == 'c'){
        creater = !creater;
    }
    if(key == 'o'){
        change_terrain_direction = -change_terrain_direction;
    }

    if(key == 'l'){
        type = -type;
    }
}




//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(creater){
        change_terrain = true;
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if(creater){
        change_terrain = false;
    }

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
