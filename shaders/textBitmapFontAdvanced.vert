#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vUV; 

layout(location = 2) in vec2 vCharacterPosition; // Integer position (column, row) of the character (e.g. (2.0, 3.0))
layout(location = 3) in float vGlyphIndex; // Index of the glyph on the spritesheet (e.g. (10))
layout(location = 4) in vec4 vGlyphColor; // Color to render the glyph in (e.g. (1.0, 1.0, 0.0, 1.0))

layout(location = 5) in vec2 vAnimWaveAmplitude; // Amplitude of the waving animation of the character
layout(location = 6) in vec2 vAnimShakeAmplitude; // Amplitude of the shaking animation of the character
layout(location = 7) in float vAnimHueCycleAmplitude; // Amount of hue cycle coloring to apply to the character
layout(location = 8) in float vAnimIntensityPulseAmplitude; // Amount of intensity pulsing to apply to the character
layout(location = 9) in float vAnimAlphaPulseAmplitude; // Amount of alpha pulsing to apply to the character

out vec2 fUV;
out vec4 fColor;

uniform ivec2 uGlyphSize; // Size of a glyph (e.g. (16, 24))
uniform ivec2 uGlyphOrigin; // Origin of a glyphs (e.g. (8.0, 0.0))
uniform ivec2 uSpriteSheetSize; // Size of the spritesheet in pixels (e.g. (256.0, 256.0))
uniform ivec2 uSpriteSheetGridSize; // Size of the sprite grid in number of cells (e.g. (16, 8))
uniform ivec2 uSpriteSheetSeparation; // Separation of sprite grid cells in pixels (e.g. (2.0, 2.0))
uniform ivec2 uSpriteSheetOrigin; // Top-left-most position of the sprite sheet (e.g. (1.0, 1.0))

uniform float uTimeSeconds; // Current time in seconds

uniform float uAnimWaveXYOffset; // Offset between the x-axis and y-axis waving animation (expressed on a 0.0 to 1.0 scale)
uniform vec2 uAnimWaveLength; // Wavelength of the waving animation of the character (expressed in number of characters)
uniform vec2 uAnimWaveFrequency; // Frequency of the waving animation of the character (expressed in Hz)
uniform vec2 uAnimShakeWaveLength; // Wavelength of the shaking animation of the character (expressed in number of characters)
uniform vec2 uAnimShakeFrequency; // Frequency of the shaking animation of the character (expressed in Hz)

uniform vec2 uAnimHueCycleWaveLength; // Wavelength of the hue cycling animation of the character (expressed in number of characters)
uniform float uAnimHueCycleFrequency; // Frequency of the hue cycling animation of the character (expressed in Hz (cycles per second))
uniform vec2 uAnimIntensityPulseWaveLength; // Wavelength of the hue intensity pulsing animation of the character (expressed in number of characters)
uniform float uAnimIntensityPulseFrequency; // Frequency of the hue intensity pulsing animation of the character (expressed in Hz (pulses per second))
uniform vec2 uAnimAlphaPulseWaveLength; // Wavelength of the alpha pulsing animation of the character (expressed in number of characters)
uniform float uAnimAlphaPulseFrequency; // Frequency of the alpha pulsing animation of the character (expressed in Hz (pulses per second))

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	float temp = vGlyphIndex;

	// Calculate the position	
	vec4 position = vec4((vCharacterPosition.x + vPosition.x) * uGlyphSize.x - uGlyphOrigin.x, (-vCharacterPosition.y + vPosition.y) * uGlyphSize.y - uGlyphOrigin.y, 0.0f, 1.0f);
	position.x += (vAnimWaveAmplitude.x * uGlyphSize.x) * sin((uAnimWaveFrequency.x * uTimeSeconds + (vCharacterPosition.x / uAnimWaveLength.x + vCharacterPosition.y / uAnimWaveLength.y)) * (2.0f * 3.1415f));
	position.y += (vAnimWaveAmplitude.y * uGlyphSize.y) * sin((uAnimWaveFrequency.y * uTimeSeconds + (vCharacterPosition.x / uAnimWaveLength.x + vCharacterPosition.y / uAnimWaveLength.y) + uAnimWaveXYOffset) * (2.0f * 3.1415f));
	position.x += (vAnimShakeAmplitude.x * uGlyphSize.x) * sin((uAnimShakeFrequency.x * uTimeSeconds + (vCharacterPosition.x / uAnimShakeWaveLength.x + vCharacterPosition.y / uAnimShakeWaveLength.y)) * (2.0f * 3.1415f));
	position.y += (vAnimShakeAmplitude.y * uGlyphSize.y) * sin((uAnimShakeFrequency.y * uTimeSeconds + (vCharacterPosition.x / uAnimShakeWaveLength.x + vCharacterPosition.y / uAnimShakeWaveLength.y) + uAnimWaveXYOffset) * (2.0f * 3.1415f));
	gl_Position = matProjection * matView * matModel * position;
	
	// Calculate the UVs
	float col = mod(vGlyphIndex, uSpriteSheetGridSize.x);
	float row = floor(vGlyphIndex / uSpriteSheetGridSize.x);	
	float UVx = float(uSpriteSheetOrigin.x + (col) * (uGlyphSize.x + uSpriteSheetSeparation.x) + vUV.x * uGlyphSize.x);
	float UVy = float(uSpriteSheetOrigin.y + (row) * (uGlyphSize.y + uSpriteSheetSeparation.y) + vUV.y * uGlyphSize.y);
	fUV = vec2(UVx / uSpriteSheetSize.x, 1.0f - UVy / uSpriteSheetSize.y);
	
	// Pass the color
	vec4 color = vGlyphColor;
	vec4 hueColor; 
	hueColor.x = (0.5f + 0.5f * sin((uAnimHueCycleFrequency * uTimeSeconds + (vCharacterPosition.x / uAnimHueCycleWaveLength.x + vCharacterPosition.y / uAnimHueCycleWaveLength.y)) * (2.0f * 3.1415f)));
	hueColor.y = (0.5f + 0.5f * sin((uAnimHueCycleFrequency * uTimeSeconds + (vCharacterPosition.x / uAnimHueCycleWaveLength.x + vCharacterPosition.y / uAnimHueCycleWaveLength.y) + (1.0f / 3.0f)) * (2.0f * 3.1415f)));
	hueColor.z = (0.5f + 0.5f * sin((uAnimHueCycleFrequency * uTimeSeconds + (vCharacterPosition.x / uAnimHueCycleWaveLength.x + vCharacterPosition.y / uAnimHueCycleWaveLength.y) + (2.0f / 3.0f)) * (2.0f * 3.1415f)));
	hueColor.w = 1.0f;
	color = (1.0f - vAnimHueCycleAmplitude) * color + (vAnimHueCycleAmplitude) * hueColor;
	float iPulseIntensity = (vAnimIntensityPulseAmplitude / 2.0f) + vAnimIntensityPulseAmplitude * sin((uAnimIntensityPulseFrequency * uTimeSeconds + (vCharacterPosition.x / uAnimIntensityPulseWaveLength.x + vCharacterPosition.y / uAnimIntensityPulseWaveLength.y)) * (2.0f * 3.1415f));
	color = (1.0f - iPulseIntensity) * color + (iPulseIntensity) * vec4(1.0f);
	float aPulseIntensity = (vAnimAlphaPulseAmplitude / 2.0f) + vAnimAlphaPulseAmplitude * sin((uAnimAlphaPulseFrequency * uTimeSeconds + (vCharacterPosition.x / uAnimAlphaPulseWaveLength.x + vCharacterPosition.y / uAnimAlphaPulseWaveLength.y)) * (2.0f * 3.1415f));
	color.w = (1.0f - aPulseIntensity) * color.w;
	
	fColor = color;
}