//
//  Terrain.cpp
//  FinalProject
//
//  Created by Bob G on 2020/12/9.
//


#include "Terrain.hpp"

Terrain::Terrain()
: Terrain(100,100,10,10)    // default values
{
}

// -------------------------------------------
Terrain::Terrain(float width, float depth, float cols, float rows)
{
    _width = width;
    _depth =  depth;
    _cols = cols;
    _rows = rows;
    normalLength = 10;


    mesh = ofMesh::plane(width,depth,cols,rows, OF_PRIMITIVE_TRIANGLES);
    

    glm::mat4 rotationMatrix =
        glm::rotate( ofDegToRad(-90), glm::vec3(1,0,0) );
    
    for (int i=0; i<mesh.getVertices().size(); i++)
    {

        mesh.getVertices()[i] =
            rotationMatrix * glm::vec4(mesh.getVertices()[i], 1);
        

        
    }


    updateNormals();
    

    originalVerts = mesh.getVertices(); // copy
}

// -------------------------------------------
void Terrain::draw()
{

    ofPushMatrix();
    ofMultMatrix( getGlobalTransformMatrix() );
    mesh.draw();
    
    ofPopMatrix();
}

// -------------------------------------------
void Terrain::drawWireframe()
{

    ofPushMatrix();
    ofMultMatrix( getGlobalTransformMatrix() );
    mesh.drawWireframe();
    ofPopMatrix();
}

// -------------------------------------------
void Terrain::drawNormals()
{

    ofPushMatrix();
    ofMultMatrix( getGlobalTransformMatrix() );
    normalLines.draw();
    ofPopMatrix();
}

// -------------------------------------------
void Terrain::applyHeightMap(ofImage& image, float minY, float maxY)
{
    for (int i=0; i<mesh.getVertices().size(); i++)
    {
        int col = i % _cols;
        int row = i / _rows;
        
        // image position:
        float x = ofMap(col, 0, _cols, 0, image.getWidth()-1, true);
        float y = ofMap(row, 0, _rows, image.getHeight()-1, 0, true);

        float b = image.getColor(x,y).getLightness();
        float height = ofMap(b, 0, 255, minY, maxY, true);
        mesh.getVertices()[i].y = height;
    }
    originalVerts = mesh.getVertices();
    updateNormals();
}


float Terrain::getheight(glm::vec2 pos_xz){
    
    
    int x = 2048+pos_xz.x ;
    int z = -pos_xz.y + 2048;
    
    
    int row = x/4;
    int col = z/4;
    if(col>1024){
        col = 1024;
    }
    if(row>1024){
        row = 1024;
    }
    float vertice = col*1024 + row;
    
    return mesh.getVertices()[vertice].y;

}

void Terrain::terrain_changer(glm::vec2 pos_xz,float direction,float type){
    int x = 2048+pos_xz.x ;
    int z = -pos_xz.y + 2048;
    
    
    int row = x/4;
    int col = z/4;
    if(col>1024){
        col = 1024;
    }
    if(row>1024){
        row = 1024;
    }

    
    for(int x=-150;x<151;x++){
        for(int y=-150;y<151;y++){
            glm::vec2 center = glm::vec2(col,row);
            glm::vec2 cur = glm::vec2(col+x,row+y);
            float distance = glm::length(cur-center);
            if(distance < 150){
                float new_row = row+x;
                float new_col = col+y;
                float vertice = new_col*1024 + new_row;
                
                if(type==1){
                    mesh.getVertices()[vertice].y += 2*ofMap(distance,0,150,10,0)*direction;
                }else{
                    mesh.getVertices()[vertice].y += 10*direction;
                }
                
            }
        }
    }
    
}

// -------------------------------------------
void Terrain::mapTexture(ofTexture texture)
{
    mesh.clearTexCoords();
    for (int i=0; i<mesh.getVertices().size(); i++)
    {

        int col = i % _cols;
        int row = i / _cols;
        

        float x = ofMap(col, 0, _cols, 0, texture.getWidth()-1, true);
        float y = ofMap(row, 0, _rows, texture.getHeight()-1, 0, true);

        
        mesh.addTexCoord( glm::vec2(x,y) );
    }
}

// -------------------------------------------
void Terrain::applyNoise( glm::vec2 spatialFreq, float amplitude, float noiseZ )
{

    
    for (int i=0; i<mesh.getVertices().size(); i++){
        
        glm::vec3& vert = mesh.getVertices()[i];
        
        glm::vec3 noisePos;
        noisePos.x = vert.x / _width * 0.5 * spatialFreq.x;
        noisePos.y = vert.z / _depth * 0.5 * spatialFreq.y;
        
        noisePos.z = noiseZ;  // apply z offset (eg. time)
        
        float noise = ofSignedNoise( noisePos ) * amplitude;
        
        vert.y = originalVerts[i].y + noise;
    }
    
    // vertices modified, update normals:
    updateNormals();
}

// -------------------------------------------
void Terrain::updateNormals()
{
    
    // make sure mesh is using correct triangle mode
    if (mesh.getMode() != OF_PRIMITIVE_TRIANGLES)
    {
        ofLogError("Terrain") << "Mesh must use ofPrimitiveMode: OF_PRIMITIVE_TRIANGLES to generate normals!";
        return;     // abort if incorrect
    }
    
    auto& verts = mesh.getVertices();
    
    
    normalLines.clear();    // extra line mesh for drawing normals
    normalLines.setMode(OF_PRIMITIVE_LINES);        // lines
    int normalIndex = 0;    // we'll use this later

    mesh.clearNormals();
    mesh.addNormals( vector<glm::vec3>(verts.size()) );

    for( int i=0; i+2 < mesh.getIndices().size(); i+=3 )
    {
        

        const int va = mesh.getIndices()[i];
        const int vb = mesh.getIndices()[i+1];
        const int vc = mesh.getIndices()[i+2];
        
        glm::vec3 e1 = verts[va] - verts[vb];
        glm::vec3 e2 = verts[vc] - verts[vb];
        glm::vec3 nml = glm::normalize(glm::cross(e2,e1));
        

        mesh.getNormals()[va] += nml;
        mesh.getNormals()[vb] += nml;
        mesh.getNormals()[vc] += nml;

        
        glm::vec3 faceCenter = getTriangleCenter(verts[va],verts[vb],verts[vc]);
        glm::vec3 normalEnd = faceCenter + nml * normalLength;

        normalLines.addVertex(faceCenter);
        normalLines.addVertex(normalEnd);
        normalLines.addIndex(normalIndex);
        normalLines.addIndex(normalIndex+1);
        normalIndex += 2;
    }
}

void Terrain::transformVertices(glm::mat4 transform)
{

    for (int i=0; i<mesh.getVertices().size(); i++)
    {
  
        
        glm::vec4 vert = glm::vec4( mesh.getVertices()[i], 1 );
        mesh.getVertices()[i] = transform * vert;

        
    }
        updateNormals();

    originalVerts = mesh.getVertices(); // copy
    
}


// helper function:
// -------------------------------------------
glm::vec3 Terrain::getTriangleCenter(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{

    glm::vec3 edgePt = (b + c) * 0.5;
    return a * .333f + edgePt * .667f;
}



