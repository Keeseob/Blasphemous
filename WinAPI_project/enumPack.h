#pragma once

enum class eSceneType
{
	title,
	play,
	begining,
	ending,
	tool,
	end,
};

enum class eLayerType
{
	background,
	monster,
	player,
	projectile,
	test,
	ground,
	effect,
	UI,
	end = 16,
};

enum class eComponentType
{
	transformation,
	spriteRender,
	animator,
	collider,
	rigidBody,
	audio,
	end,
};