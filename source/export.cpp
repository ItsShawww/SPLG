#include"export.h"

void exportFn(Grid grid, const std::string& filename){
    std::ofstream outfile(filename);
    
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for export!\n";
        return;
    }

    for (const auto& cell : grid.gridCells) {
        if (cell.gate == NONE) continue;

        std::string functionName = "";
        if (cell.gate == AND) functionName = "splg:cland";
        else if (cell.gate == OR) functionName = "splg:clor";
        else if (cell.gate == NOT) functionName = "splg:clnot";
        int worldX = cell.x;
        int worldY = -60; 
        int worldZ = cell.y;

        outfile << "function " << functionName << " {x:" << worldX << ", y:" << worldY << ", z:" << worldZ << "}\n";
    }

    outfile.close();
    std::cout << "Successfully exported layout to " << filename << "!\n";
}
