#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    bool patternH[3][3] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    };
    CustomMatrix det_H(patternH);

    bool patternV[3][3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    CustomMatrix det_V(patternV);

    bool patternD1[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    CustomMatrix det_D1(patternD1);

    bool patternD2[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };
    CustomMatrix det_D2(patternD2);

    std::vector<CustomMatrix> detectors = {det_H, det_V, det_D1, det_D2};

    m_segment_candidates.clear();

    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){

            if (image.pixel(i, j) == 0xffffffff) {
                continue;
            }

            bool local_window[3][3] = {false};
            bool is_non_empty_window = false;

            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    bool is_drawing = (rgbValue != 0xffffffff);
                    local_window[m+1][n+1] = is_drawing;
                    if (is_drawing) {
                        is_non_empty_window = true;
                    }
                }
            }

            if (!is_non_empty_window) continue;

            CustomMatrix current_mat(local_window);
r
            bool is_match = false;
            for (const auto& detector : detectors) {
                if (compareMatrices(current_mat, detector)) {
                    is_match = true;
                    break;
                }
            }


            if (is_match) {
                m_segment_candidates.append(QPoint(i, j));
            }
        }
    }

    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        isPaintLinesClicked = false;

        // return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }

    if (!m_segment_candidates.isEmpty()) {
        pen.setColor(Qt::darkMagenta); 
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setBrush(QBrush(Qt::darkMagenta));

        const int size = 3;

        for (const QPoint& point : std::as_const(m_segment_candidates)) {
            painter.drawRect(point.x() - 1, point.y() - 1, size, size);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


