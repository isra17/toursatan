#include "CImgAnim.h"

CImgAnim::CImgAnim(const sf::Image &Img, const unsigned int &nbFrame, const unsigned int &line, const unsigned int &maxLine,
			const sf::Vector2f &Position, const sf::Vector2f &Scale,float Rotation, const sf::Color &Col)
: sf::Sprite(Img,Position,Scale,Rotation,Col)
{
	m_animRow=0;
	//Le constructeur par défaut prend en compte qu'il n'y a aucun offset
	SetSubRect(sf::IntRect(0,0,Img.GetWidth()/line,Img.GetHeight()/maxLine));
	m_xOffset=0;
	m_yOffset=0;
	m_size=nbFrame;
}


void CImgAnim::setAnimRow(const unsigned int &row)
{
	m_animRow=row;
	refreshSubRect();
}

int CImgAnim::animRow() const
{
	return m_animRow;
}

void CImgAnim::setFrameDim(const unsigned int &w, const unsigned int &h)
{
	sf::IntRect tRect = GetSubRect();
	//Prend le subrect deja existant et ajuste sa taille en le laissant a la meme position
	SetSubRect(sf::IntRect(tRect.Left,tRect.Top,tRect.Left+w,tRect.Top+h));
}

sf::IntRect CImgAnim::frameDim() const
{
	sf::IntRect tRect = GetSubRect();
	return sf::IntRect(0,0,tRect.GetWidth(),tRect.GetHeight());
}

void CImgAnim::setOffset(const unsigned int &x, const unsigned int &y)
{
	m_xOffset=x;
	m_yOffset=y;

	refreshSubRect();
}

sf::IntRect CImgAnim::offset() const
{
	return sf::IntRect(0,0,m_xOffset,m_yOffset);
}

int unsigned CImgAnim::getSize() const
{
	return m_size;
}

void CImgAnim::setSize(const unsigned int &size)
{
	m_size=size;
}


void CImgAnim::setFrame(const unsigned int &count)
{
	CAnim::setFrame(count);
	refreshSubRect();
}

void CImgAnim::refreshSubRect()
{
	sf::IntRect tRect = GetSubRect();
	//met a jour le subrect selon le frame courant et l'offset

	SetSubRect(sf::IntRect(tRect.GetWidth()*m_animRow				+m_xOffset,
							tRect.GetHeight()*currentFrame()		+m_yOffset,
							tRect.GetWidth()*(m_animRow+1)			+m_xOffset,
							tRect.GetHeight()*(currentFrame()+1)	+m_yOffset));
}


void CImgAnim::Render(sf::RenderTarget& target) const
{
	//Cast pour pouvoir appeler update puisque celui-ci n'est pas constant (il change de frame)
	CImgAnim* th = const_cast<CImgAnim*>(this);
	th->update();
	sf::Sprite::Render(target);
}
