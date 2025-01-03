#include"raylib.h"
#include<math.h>
#include<stdlib.h>

/*creating the window*/

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define NEURON_RADIUS 20

/*Defining a neuron*/

typedef struct Neuron {
    float x, y;
    Color color;
    float alpha;
} Neuron;

/*Creating a neuron*/

Neuron CreateNeuron(float x, float y, Color color, float alpha) {
    Neuron neuron;
    neuron.x = x;
    neuron.y = y;
    neuron.color = color;
    neuron.alpha = alpha;
    return neuron;
}

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neural Network Visualization");
    SetTargetFPS(60);

    /*How's this neural network made (layers & neurons per layer) */
   
    int num_layers = 5;
    int neurons_per_layer[] = {8, 10, 10, 10, 1};

    /*Layers space horizontally*/
    
    float layer_spacing = SCREEN_WIDTH / (num_layers + 1);

    /*Neuron vertical spacing per layer*/
    Neuron neurons[5][10]; 

    for (int i = 0; i < num_layers; i++) {
        int num_neurons = neurons_per_layer[i];
        float vertical_spacing = SCREEN_HEIGHT / (num_neurons + 1);

        for (int j = 0; j < num_neurons; j++) {
            float x = (i + 1) * layer_spacing;
            float y = (j + 1) * vertical_spacing;
            Color color = (i == 0) ? BLUE : ((i == num_layers - 1) ? RED : GREEN);
            neurons[i][j] = CreateNeuron(x, y, color, 0.3f);
        }
    }
    
    float time = 0.0f;   /*initialize time to 0 to start the program*/
    int active_layer = 0;
    int direction = 1;
    float layer_duration = 2.0;
    float layer_progress = 0.0;
   
    
    while (!WindowShouldClose()) {
        time += GetFrameTime();
        layer_progress += GetFrameTime();

         /* Switch active layer when layer_progress exceeds duration*/
       
        if (layer_progress > layer_duration) {
            layer_progress = 0.0;
            active_layer += direction;
            if (active_layer == 0 || active_layer == num_layers - 1) {
                direction *= -1;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        /*Connecting the layers*/
        
        for (int i = 0; i < num_layers - 1; i++) {
            int num_neurons_current = neurons_per_layer[i];
            int num_neurons_next = neurons_per_layer[i + 1];

            for (int j = 0; j < num_neurons_current; j++) {
                for (int k = 0; k < num_neurons_next; k++) {
                    float alpha = (i == active_layer || i + 1 == active_layer) ? 0.8f : 0.3f;

                    DrawLineEx(
                        (Vector2){neurons[i][j].x, neurons[i][j].y},
                        (Vector2){neurons[i + 1][k].x, neurons[i + 1][k].y},
                        2.0f,
                        Fade(GRAY, alpha)
                    );
                }
            }
        }


        /* Draw neurons*/
       
        for (int i = 0; i < num_layers; i++) {
            int num_neurons = neurons_per_layer[i];
            for (int j = 0; j < num_neurons; j++) {

                if (i== active_layer) {
                neurons[i][j].alpha = 0.3f + 0.7f * fabs(sin(layer_progress / layer_duration * PI ));
                } else {
                    neurons[i][j].alpha = 0.3f;
            }

                DrawCircleV(
                    (Vector2){neurons[i][j].x, neurons[i][j].y},
                    NEURON_RADIUS,
                    Fade(neurons[i][j].color, neurons[i][j].alpha)
                    );
        }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
