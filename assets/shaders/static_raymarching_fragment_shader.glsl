#version 450 core

in vec2 uv;

uniform vec3 playerPos;
uniform vec3 playerFwd;
uniform vec3 playerRight;
uniform vec3 playerUp;
uniform float inverseScreenRatio;

float sdBox(vec3 p, vec3 b)
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float DE(vec3 p)
{
   float d = sdBox(p,vec3(1.0));

   float s = 2.67;
   for( int m=0; m<8; m++ )
   {
      vec3 a = mod( p*s, 2.0 )-1.0;
      s *= 3.0;
      vec3 r = abs(1.0 - 3.0*abs(a));

      float da = max(r.x,r.y);
      float db = max(r.y,r.z);
      float dc = max(r.z,r.x);
      float c = (min(da,min(db,dc))-1.0)/s;

      d = max(d,c);
   }

   return d;
}

float map( in vec3 rayP)
{
	float Scale = 100.0;
	return DE(rayP/Scale)*Scale;
}

vec2 interesct( in vec3 ro, in vec3 rd, in float tmax )
{
    float t = 0.0;
	float i=0.0;
	for( i=0.0; i<128.0; i++ )
	{
        vec3 rayP = ro + t*rd;
		float d = map(rayP);
		if(d<(0.0001*t) ||  t>tmax ) return vec2(t, i);
		t += d;
	}

	return vec2(t, i);
}

vec3 calcNormal(vec3 p) {
	float e = 0.0001;
    return normalize(vec3(
        map(vec3(p.x + e, p.y, p.z)) - map(vec3(p.x - e, p.y, p.z)),
        map(vec3(p.x, p.y + e, p.z)) - map(vec3(p.x, p.y - e, p.z)),
        map(vec3(p.x, p.y, p.z  + e)) - map(vec3(p.x, p.y, p.z - e))
    ));
}

vec3 render( in vec3 ro, in vec3 rd )
{
	float colorInvert = 1.0; // can be turned to zero, dont forget to switch minus signs then!

    //lights, point light at player position
	vec3 light = -normalize(rd);

    // bounding plane
    float tmax = 1024.0;

	vec3 col;
	vec2 rayData = interesct(ro, rd, tmax);
    float t = rayData.x;
    
	//colors
	vec3 skyColor = vec3(0.1);//vec3(0.56, 0.74, 0.53)*0.75;
	vec3 solidColor = vec3(0.72, 0.86, 0.89);

	if( t>tmax)
    {
        // sky		
		col = skyColor;
	}
	else
	{		
		//lighting
		vec3 rayP = ro + t*rd;
        vec3 nor = calcNormal(rayP);

		float distOcclusion = 1.0 - rayData.y * 2.0 / 256.0;
		float diffLighting = clamp(dot(light, nor), 0.0, 1.0);
		
		//inverted specular lighting, darkens the reflections, which lightens after inversion 
		float specLighting = colorInvert - pow(clamp(dot(nor, normalize(light-rd)),0.0,1.0), 32.0);

		float combinedShading = diffLighting * 0.35 + distOcclusion * 0.4 + specLighting * 0.15 + 0.1;

		col = solidColor * combinedShading;

		//apply fog
		float fogStrength = exp(-t*0.01);
		col = skyColor*(1.0-fogStrength) + col*fogStrength;
		
	}
	
	//inverting colors and contrast enhancing
	col = vec3(colorInvert) - col;
	col = vec3(col.x*col.x,col.y*col.y,col.z*col.z);

	return col;
}

void main(void)
{

	vec2 ScreenPos = uv.xy - vec2(0.5, 0.5);

    // camera position
	vec3 ro = playerPos;
	
    // camera rays    
	vec3 rd = normalize(playerFwd + playerRight * ScreenPos.x + playerUp * -ScreenPos.y * inverseScreenRatio);
    vec3 col = render( ro, rd );
    
    gl_FragColor = vec4( col, 1.0 );
}