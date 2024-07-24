#ifndef FLATWORLD_H
#define FLATWORLD_H

#include "FlatVector.h"
#include "FlatBody.h"
#include "FlatMath.h"
#include <vector>

namespace FlatPhysics {

    struct GridCell {
        std::vector<FlatBody> bodies;
    };

    struct Grid {
        int rows;
        int cols;
        float width;
        float height;
        std::vector<std::vector<GridCell>> cells;

        Grid(int rows, int cols, float width, float height) : rows(rows), cols(cols), width(width), cells(rows, std::vector<GridCell>(cols)) {}

        void clear() {
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    cells[r][c].bodies.clear();
                }
            }
        }
        void addBody(const FlatBody& body) {
            int col = static_cast<int>(body.GetPosition().x() / width);
            int row = static_cast<int>(body.GetPosition().y() / height);
            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                cells[row][col].bodies.push_back(body);
            }
        }
    };

    class FlatWorld {
        public:
            static float minDensity;
            static float maxDensity;

            static float minSize;
            static float maxSize;

            FlatWorld();

            void step(float time);
            std::vector<FlatBody> getBodies();

            void addBody(FlatBody body);
            void setConstraint(FlatVector position, float radius);
            void solveCollisions();

        private:
            FlatVector gravity;
            std::vector<FlatBody> bodyList;

            FlatVector constraint_center;
            float constraint_radius;

            void applyConstraint();
    };

} 

#endif 