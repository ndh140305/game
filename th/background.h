#ifndef __BACKGROUND_H
#define __BACKGROUND_H

struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture)
    {
        texture = _texture;
        if (texture == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
            "Could not load bg! SDL_IMG Error: %s", IMG_GetError());
        }
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance)
    {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 )
        {
            scrollingOffset = height;
        }
    }
};

void render(SDL_Renderer* _renderer ,const ScrollingBackground& background)
{
        renderTexture(_renderer , background.texture, 0 , background.scrollingOffset);
        renderTexture(_renderer , background.texture, 0, background.scrollingOffset - background.height);
}

ScrollingBackground create_bg(SDL_Renderer* renderer)
{
    ScrollingBackground background;
    background.setTexture(IMG_LoadTexture(renderer , "img//background.jpg"));
    return background;
}


void load_bg(SDL_Renderer* renderer , ScrollingBackground& background)
{
    SDL_RenderClear(renderer);
    background.scroll(1);
    render(renderer , background);
}
#endif // __BACKGROUND_H
