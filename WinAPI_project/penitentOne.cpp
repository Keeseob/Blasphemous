#include "penitentOne.h"
#include "time.h"
#include "sceneManager.h"
#include "keyInput.h"
#include "bpResources.h"
#include "transformation.h"
#include "animator.h"
#include "collider.h"
#include "projectile.h"
#include "sceneManager.h"
#include "object.h"
#include "rigidBody.h"

namespace BP
{
	penitentOne::penitentOne()
	{
	}
	penitentOne::~penitentOne()
	{
	}

	void penitentOne::initialize()
	{
		//penitentOne 시작 위치
		//transformation* trns = getComponent<transformation>();
		//trns->setPosition(vector2(1000.0f, 1150.0f));

		image* mImage = bpResources::load<image>(L"penitentOne", L"..\\Resource\\penitent_anim.bmp");
		mAnimator = addComponent<animator>();
		mAnimator->createAnimation(L"idleRight", mImage
			, vector2::zero, 14, 10, 13
			, vector2(-40.0f, -40.0f), 0.05);
		mAnimator->createAnimation(L"idleLeft", mImage
			, vector2(0.0f, 140.0f), 14, 10, 13
			, vector2(-40.0f, -40.0f), 0.05);

		mAnimator->createAnimation(L"runRight_start", mImage
			, vector2(0.0f, 280.0f), 14, 9, 7
			, vector2(-30.0f, -25.0f), 0.02);
		mAnimator->createAnimation(L"runLeft_start", mImage
			, vector2(0.0f, 420.0f), 14, 9, 7
			, vector2(-50.0f, -25.0f), 0.02);

		mAnimator->createAnimation(L"runRight", mImage
			, vector2(0.0f, 560.0f), 14, 10, 14
			, vector2(-30.0f, -40.0f), 0.03);
		mAnimator->createAnimation(L"runLeft", mImage
			, vector2(0.0f, 700.0f), 14, 9, 14
			, vector2(-50.0f, -25.0f), 0.03);

		mAnimator->createAnimation(L"jumpRight", mImage	, vector2(0.0f, 840.0f), 14, 10, 3, vector2(-50.0f, -40.0f), 0.1);
		mAnimator->createAnimation(L"jumpLeft", mImage, vector2(0.0f, 980.0f), 14, 10, 3, vector2(-50.0f, -40.0f), 0.1);
		mAnimator->createAnimation(L"landRight", mImage, vector2(420.0f, 840.0f), 14, 10, 7, vector2(-50.0f, -40.0f), 0.05);
		mAnimator->createAnimation(L"landLeft", mImage, vector2(420.0f, 980.0f), 14, 10, 7, vector2(-50.0f, -40.0f), 0.05);

		mAnimator->createAnimation(L"crouchRight", mImage
			, vector2(0.0f, 1120.0f), 14, 10, 7
			, vector2(-50.0f, -40.0f), 0.04);
		mAnimator->createAnimation(L"crouchLeft", mImage
			, vector2(0.0f, 1260.0f), 14, 10, 7
			, vector2(-50.0f, -40.0f), 0.04);

		mAnimator->createAnimations(L"..\\Resource\\penitent_attack_anim", vector2(-65.0f, 0.0f), 0.02f);
		mAnimator->createAnimations(L"..\\Resource\\penitent_attack_anim_L", vector2(-65.0f, 0.0f), 0.02f);
		mAnimator->createAnimations(L"..\\Resource\\penitent_jump_attack_anim", vector2(-120.0f, +40.0f), 0.02f);
		mAnimator->createAnimations(L"..\\Resource\\penitent_jump_attack_anim_L", vector2(-120.0f, +40.0f), 0.02f);

		mAnimator->play(L"idleRight", true);
		mState = ePenitentState::idleRight;

		collider* coll = addComponent<collider>();
		coll->setCenter(vector2(-5.0f, 0.0f));
		coll->setSize(vector2(70.0f, 100.0f));

		mRigidBody = addComponent<rigidBody>();
		mRigidBody->setMass(1.00f);

		//mAnimator->createAnimations(L"..\\Resource\\crisantaMenu", vector2::zero, 0.3f);
		//mAnimator->getStartEvent(L"idleRight") = std::bind(&penitentOne::idleRight, this);
		//mAnimator->getCompleteEvent(L"idleLeft") = std::bind(&penitentOne::idleLeft, this);
		//mAnimator->getEndEvent(L"jumpRight") = std::bind(&penitentOne::jumpRight, this);


		gameObject::initialize();
	}

	void penitentOne::update()
	{
		switch (mState)
		{
		case BP::penitentOne::ePenitentState::idleRight: idleRight(); break;
		case BP::penitentOne::ePenitentState::idleLeft: idleLeft();	break;

		case BP::penitentOne::ePenitentState::runRight_start: runRight_start();	break;
		case BP::penitentOne::ePenitentState::runLeft_start: runLeft_start(); break;
		case BP::penitentOne::ePenitentState::runRight: runRight(); break;
		case BP::penitentOne::ePenitentState::runLeft: runLeft(); break;

		case BP::penitentOne::ePenitentState::jumpRight: jumpRight(); break;
		case BP::penitentOne::ePenitentState::jumpLeft: jumpLeft(); break;

		case BP::penitentOne::ePenitentState::crouchRight: crouchRight(); break;
		case BP::penitentOne::ePenitentState::crouchLeft: crouchLeft();	break;

		case BP::penitentOne::ePenitentState::attack: attack();	break;
		case BP::penitentOne::ePenitentState::attackL: attackL(); break;
		case BP::penitentOne::ePenitentState::jumpAttack: jumpAttack(); break;

		case BP::penitentOne::ePenitentState::death: death(); break;

		default:
			break;
		}

		gameObject::update();
	}

	void penitentOne::render(HDC hdc)
	{
		gameObject::render(hdc);
	}

	void penitentOne::release()
	{
		gameObject::release();
	}

	void penitentOne::onCollisionEnter(collider* other)
	{
	}
	void penitentOne::onCollisionStay(collider* other)
	{
	}
	void penitentOne::onCollisionExit(collider* other)
	{
	}

	void penitentOne::idleRight()
	{
		if (keyInput::getKey(eKeyCode::D))
		{
			mState = ePenitentState::runRight_start;
			mAnimator->play(L"runRight_start", false);
		}
		if (keyInput::getKey(eKeyCode::A))
		{
			mState = ePenitentState::runLeft_start;
			mAnimator->play(L"runLeft_start", false);
		}

		if (keyInput::getKey(eKeyCode::S))
		{
			mState = ePenitentState::crouchRight;
			mAnimator->play(L"crouchRight", false);
		}

		if (keyInput::getKey(eKeyCode::K))
		{
			mState = ePenitentState::attack;
			mAnimator->play(L"Resourcepenitent_attack_anim", false);
		}
		if (keyInput::getKey(eKeyCode::L))
		{
			mState = ePenitentState::jumpAttack;
			mAnimator->play(L"Resourcepenitent_jump_attack_anim", false);
		}

		if (keyInput::getKeyDown (eKeyCode::space))
		{
			mAnimator->play(L"jumpRight", false);

			vector2 velocity = mRigidBody->getVelocity();
			velocity.y -= 450.0f;

			mRigidBody->setVelocity(velocity);
			mRigidBody->setGround(false);
			//pos.y -= 100.0f * time::deltaTime();
		}
		if (keyInput::getKeyUp(eKeyCode::space))
		{
			mAnimator->play(L"landRight", false);
			mState = ePenitentState::idleRight;
		}
	}
	void penitentOne::idleLeft()
	{
		if (keyInput::getKey(eKeyCode::A))
		{
			mState = ePenitentState::runLeft_start;
			mAnimator->play(L"runLeft_start", false);
		}
		if (keyInput::getKey(eKeyCode::D))
		{
			mState = ePenitentState::runRight_start;
			mAnimator->play(L"runRight_start", false);
		}

		if (keyInput::getKeyDown(eKeyCode::S))
		{
			mState = ePenitentState::crouchLeft;
			mAnimator->play(L"crouchLeft", false);
		}
		if (keyInput::getKey(eKeyCode::K))
		{
			mState = ePenitentState::attackL;
			mAnimator->play(L"Resourcepenitent_attack_anim_L", false);
		}
		if (keyInput::getKey(eKeyCode::L))
		{
			mState = ePenitentState::jumpAttack;
			mAnimator->play(L"Resourcepenitent_jump_attack_anim_L", false);
		}

		if (keyInput::getKeyDown(eKeyCode::space))
		{
			mAnimator->play(L"jumpLeft", false);

			vector2 velocity = mRigidBody->getVelocity();
			velocity.y -= 450.0f;

			mRigidBody->setVelocity(velocity);
			mRigidBody->setGround(false);
			//pos.y -= 100.0f * time::deltaTime();
		}
		if (keyInput::getKeyUp(eKeyCode::space))
		{
			mAnimator->play(L"landLeft", false);
			mState = ePenitentState::idleLeft;
		}
	}

	void penitentOne::runRight_start()
	{
		if (keyInput::getKeyUp(eKeyCode::D))
		{
			mState = ePenitentState::idleRight;
			mAnimator->play(L"idleRight", true);
		}
		if (keyInput::getKey(eKeyCode::D))
		{
			mState = ePenitentState::runRight;
			mAnimator->play(L"runRight", true);
		}
	}
	void penitentOne::runLeft_start()
	{
		if (keyInput::getKeyUp(eKeyCode::A))
		{
			mAnimator->play(L"idleLeft", true);
			mState = ePenitentState::idleLeft;
		}
		if (keyInput::getKey(eKeyCode::A))
		{
			mState = ePenitentState::runLeft;
			mAnimator->play(L"runLeft", true);
		}
	}

	void penitentOne::runRight()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::D))
		{
			mAnimator->play(L"idleRight", true);
			mState = ePenitentState::idleRight;
		}
		if (keyInput::getKey(eKeyCode::D))
		{
			//mState = ePenitentState::runRight;
			//mAnimator->play(L"runRight", true);
			//mRigidBody->addForce(vector2(200.0f, 0.0f));
			pos.x += 200.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
	void penitentOne::runLeft()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::A))
		{
			mAnimator->play(L"idleLeft", true);
			mState = ePenitentState::idleLeft;
		}
		if (keyInput::getKey(eKeyCode::A))
		{
			//mRigidBody->addForce(vector2(-200.0f, 0.0f));
			pos.x -= 200.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void penitentOne::jumpRight()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::space))
		{
			mAnimator->play(L"idleRight", true);
			mState = ePenitentState::idleRight;
		}
		trns->setPosition(pos);
	}
	void penitentOne::jumpLeft()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::space))
		{
			mAnimator->play(L"idleLeft", true);
			mState = ePenitentState::idleLeft;
		}
		if (keyInput::getKey(eKeyCode::W))
		{
			//pos.y -= 100.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void penitentOne::crouchRight()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::S))
		{
			mAnimator->play(L"idleRight", true);
			mState = ePenitentState::idleRight;
		}
		if (keyInput::getKey(eKeyCode::S))
		{
			//pos.y += 100.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
	void penitentOne::crouchLeft()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::S))
		{
			mAnimator->play(L"idleLeft", true);
			mState = ePenitentState::idleLeft;
		}
		if (keyInput::getKey(eKeyCode::S))
		{
			//pos.y += 100.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void penitentOne::attack()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::K))
		{
			mAnimator->play(L"idleRight", true);
			mState = ePenitentState::idleRight;
		}
		if (keyInput::getKey(eKeyCode::K))
		{
			obj::instantiate<projectile>(vector2(190.0f, 700.0f), eLayerType::projectile, eSceneType::play);
			trns->setPosition(pos);
		}
	}

	void penitentOne::attackL()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKeyUp(eKeyCode::K))
		{
			mAnimator->play(L"idleLeft", true);
			mState = ePenitentState::idleLeft;
		}
		if (keyInput::getKey(eKeyCode::K))
		{
			obj::instantiate<projectile>(vector2(190.0f, 700.0f), eLayerType::projectile, eSceneType::play);
			trns->setPosition(pos);
		}
	}

	void penitentOne::jumpAttack()
	{
		transformation* trns = getComponent<transformation>();

		if (keyInput::getKeyUp(eKeyCode::L))
		{
			mAnimator->play(L"idleRight", true);
			mState = ePenitentState::idleRight;
		}
	}

	void penitentOne::death()
	{
	}

	void penitentOne::idleCompleteEvent(/*const penitentOne* this*/)
	{
	}
}
