#include "image.h"
#include "application.h"
#include "bpResources.h"

extern BP::application bp_application;

namespace BP
{
	image* image::create(const std::wstring& name, UINT width, UINT height, COLORREF rgb)
	{
		if (width == 0 || height == 0) { return nullptr; }
		image* img = bpResources::find<image>(name);
		if (img != nullptr) { return img; }

		img = new image();
		HDC mainHdc = bp_application.getHdc();
		img->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		img->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(img->mHdc, img->mBitmap);
		DeleteObject(oldBitmap);

		img->mWidth = width;
		img->mHeight = height;

		img->setKey(name);
		bpResources::insert<image>(name, img);

		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(img->getHdc(), brush);

		//이미지 색 설정
		Rectangle(img->getHdc(), -1, -1, img->mWidth + 1, img->mHeight + 1);
		SelectObject(img->getHdc(), oldBrush);
		DeleteObject(oldBrush);
		return img;
	}

	image::image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}
	image::~image()
	{
	}

	HRESULT image::load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str(), IMAGE_BITMAP
			, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr) { return E_FAIL; }

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDc = bp_application.getHdc();
		mHdc = CreateCompatibleDC(mainDc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
}
