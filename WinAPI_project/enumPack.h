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
	background4,
	background3,
	background2,
	background,
	monster,
	player,
	projectile,
	test,
	ground,
	effect,
	UI,
	foreground,
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