#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vUV; 

layout(location = 2) in vec2 vCharacterPosition; // Integer position (column, row) of the character (e.g. (2.0, 3.0))
layout(location = 3) in float vGlyphIndex; // Index of the glyph on the spritesheet (e.g. (10))
layout(location = 4) in vec4 vGlyphColor; // Color to render the glyph in (e.g. (1.0, 1.0, 0.0, 1.0))

out vec2 fUV;
out vec4 fColor;

uniform ivec2 uGlyphSize; // Size of a glyph (e.g. (16, 24))
uniform ivec2 uGlyphOrigin; // Origin of a glyphs (e.g. (8.0, 0.0))
uniform ivec2 uSpriteSheetSize; // Size of the spritesheet in pixels (e.g. (256.0, 256.0))
uniform ivec2 uSpriteSheetGridSize; // Size of the sprite grid in number of cells (e.g. (16, 8))
uniform ivec2 uSpriteSheetSeparation; // Separation of sprite grid cells in pixels (e.g. (2.0, 2.0))
uniform ivec2 uSpriteSheetOrigin; // Top-left-most position of the sprite sheet (e.g. (1.0, 1.0))

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

void main()
{
	// Calculate the position	
	vec4 position = vec4((vCharacterPosition.x + vPosition.x) * uGlyphSize.x - uGlyphOrigin.x, (-vCharacterPosition.y + vPosition.y) * uGlyphSize.y - uGlyphOrigin.y, 0.0f, 1.0f);
	gl_Position = matProjection * matView * matModel * position;
	
	// Calculate the UVs
	float col = mod(vGlyphIndex, uSpriteSheetGridSize.x);
	float row = floor(vGlyphIndex / uSpriteSheetGridSize.x);	
	float UVx = float(uSpriteSheetOrigin.x + (col) * (uGlyphSize.x + uSpriteSheetSeparation.x) + vUV.x * uGlyphSize.x);
	float UVy = float(uSpriteSheetOrigin.y + (row) * (uGlyphSize.y + uSpriteSheetSeparation.y) + vUV.y * uGlyphSize.y);
	fUV = vec2(UVx / uSpriteSheetSize.x, 1.0f - UVy / uSpriteSheetSize.y);
	
	// Pass the color
	fColor = vGlyphColor;
}