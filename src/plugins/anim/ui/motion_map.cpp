#include "motion_map.h"

#include <QGraphicsSceneWheelEvent>
#include <QGraphicsWidget>
#include <QWidget>
#include <QScrollBar>

namespace anim { namespace ui {

MotionMap::MotionMap() : m_pixmap(new QGraphicsPixmapItem()) {
	m_scene = new QGraphicsScene(this);
	setScene(m_scene);

	m_scene->addItem(m_pixmap);
}

void MotionMap::init(const ::anim::MotionMap& mmap) {
	QImage img = QImage(mmap.width(), mmap.height(), QImage::Format_RGB32);

	for(unsigned y = 0; y < mmap.height(); ++y)
		for(unsigned x = 0; x < mmap.width(); ++x) {
			const float val = ((mmap(x, y) - mmap.min()) / (mmap.max() - mmap.min())) * 255.0f;
			img.setPixel(x, y, qRgb(val, val, val));
		}

	m_pixmap->setPixmap(QPixmap::fromImage(img));
}

std::size_t MotionMap::width() const {
	return m_pixmap->pixmap().width();
}

std::size_t MotionMap::height() const {
	return m_pixmap->pixmap().height();
}

void MotionMap::mouseMoveEvent(QMouseEvent* mouseEvent) {
	if(mouseEvent->buttons() & Qt::MiddleButton) {
		const QPoint d = mouseEvent->pos() - m_mousePos;
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - d.x());
		verticalScrollBar()->setValue(verticalScrollBar()->value() - d.y());
	}

	emit mouseMove(mouseEvent);

	m_mousePos = mouseEvent->pos();
}

void MotionMap::mousePressEvent(QMouseEvent* mouseEvent) {
	emit mousePress(mouseEvent);

	m_mousePos = mouseEvent->pos();
}

void MotionMap::mouseReleaseEvent(QMouseEvent* mouseEvent) {
	emit mouseRelease(mouseEvent);

	m_mousePos = mouseEvent->pos();
}

namespace {

void adjustScrollBar(QScrollBar* scrollBar, float factor, float pos) {


	scrollBar->setValue(int(factor * scrollBar->value()
	                        + ((factor - 1) * scrollBar->pageStep() * pos)));
}

}

void MotionMap::wheelEvent(QWheelEvent* mouseEvent) {
	const float sc = powf(10.0f, (float)mouseEvent->delta() / 480.0f);

	QPointF pos = mouseEvent->pos();

	setTransformationAnchor(QGraphicsView::NoAnchor);
	scale(sc, sc);

	adjustScrollBar(horizontalScrollBar(), sc, pos.x() / (float)QGraphicsView::width());
	adjustScrollBar(verticalScrollBar(), sc, pos.y() / (float)QGraphicsView::height());
}

} }
