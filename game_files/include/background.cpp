uniform float offset;

void main() {
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_TexCoord[0].x = gl_TexCoord[0].x + offset;
  gl_FrontColor = gl_Color;
}
