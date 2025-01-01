#include"raylib.h"
#include<math.h>
#include<stdlib.h>

/*creating the window*/

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define NEURON_RADIUS 30

/*Defining a neuron*/

typedef struct Neuron {
    float x, y;
    float base_y;
    Color color;
} Neuron;

/*Creating a neuron*/

Neuron CreateNeuron(float x, float y, Color color) {
    Neuron neuron;
    neuron.x = x;
    neuron.y = y;
    neuron.base_y = y;
    neuron.color = color;
    return neuron;
}

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neural Network Visualization");
    SetTargetFPS(60);

    /*How's this neural network made (layers & neurons per layer) */
   
    int num_layers = 4;
    int neurons_per_layer[] = {2, 4, 4, 1};

    /*Layers positioned horizontally*/
    
    float layer_spacing = SCREEN_WIDTH / (num_layers + 1);

    /*Neuron vertical spacing per layer*/
    Neuron neurons[10][10]; 

    for (int i = 0; i < num_layers; i++) {
        int num_neurons = neurons_per_layer[i];
        float vertical_spacing = SCREEN_HEIGHT / (num_neurons + 1);

        for (int j = 0; j < num_neurons; j++) {
            float x = (i + 1) * layer_spacing;
            float y = (j + 1) * vertical_spacing;
            Color color = (i == 0) ? BLUE : ((i == num_layers - 1) ? RED : GREEN);
            neurons[i][j] = CreateNeuron(x, y, color);
        }
    }
    
    float time = 0.0f;     /*initialize time to 0 to start the program*/

    while (!WindowShouldClose()) {
        time += GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        /*Connecting the layers*/
        
        for (int i = 0; i < num_layers - 1; i++) {
            int num_neurons_current = neurons_per_layer[i];
            int num_neurons_next = neurons_per_layer[i + 1];

            for (int j = 0; j < num_neurons_current; j++) {
                for (int k = 0; k < num_neurons_next; k++) {
                    DrawLine(
                        neurons[i][j].x, neurons[i][j].y,
                        neurons[i + 1][k].x, neurons[i + 1][k].y,
                        GRAY
                    );
                }
            }
        }

        /* Draw neurons*/
       
        for (int i = 0; i < num_layers; i++) {
            int num_neurons = neurons_per_layer[i];
            for (int j = 0; j < num_neurons; j++) {
                neurons[i][j].y = neurons[i][j].base_y + sin(time + neurons[i][j].x * 0.01f) * 10.0f; /*Adds a wiggling effect*/
                DrawCircleV((Vector2){neurons[i][j].x, neurons[i][j].y}, NEURON_RADIUS, neurons[i][j].color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
