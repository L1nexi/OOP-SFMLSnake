贪吃蛇作业设计说明
===================

作业简介：修改 Github 上的一个 Snake 游戏项目，添加一些特性和功能，需要满足下面的需求。

1.  贪食蛇的控制

源代码只支持 4 个方向的运行，增加可以通过鼠标控制贪食蛇的运动。当按下鼠标键时，设置一个方向向量 ， 该方向向量为鼠标所在位置 (MousePosition) 与蛇头所在位置 (SnakePosition) 的差值。下一时刻，贪食蛇按照该向量的方向运动；运动的距离为 1 个标准单位。

2.  水果的控制

源代码只支持 1 种水果，颜色随机且贪食蛇增加的长度固定。现增加黑色、棕色、红、蓝色、绿色、共 5 种水果，且贪食蛇吃了黑色、棕色水果不增加其长度，红色、蓝色、绿色水果增加的长度分别为 3、2、1；增加的长度在贪食蛇的尾部—假设初始是叠加在一起的。 系统随机生成上述 5 种水果，保持黑色和褐色水果所占比例为 25%，其他的占 75%。

3.  绘制精灵版本的贪食蛇

源代码中的贪食蛇绘制过于简单—仅仅使用了矩形绘制。要求更改贪食蛇的绘制方法，头部使用图片，通过 Sprite 进行绘制。

4.  整体界面的修改

可以修改背景的颜色（提供白色、黑色、褐色三种）；允许显示（或关闭显示）网格，网格的颜色可以设置（提供白色、黑色、褐色三种）。

5.  理清代码

代码中，要仔细考虑水果、蛇(蛇头、其他节点)、网格等对象的生命周期，确保你设计的对象周期模型是经济可靠的。

> 原作者：https://github.com/jhpy1024/sfSnake
-------------------
### 编译环境
-   操作系统：Window11
-   IDE:  Visual Studio Code
-   构建工具：CMake
-   库：SFML-2.5.1 所有模块的 Release 库，以及位于 `SFML-2.5.1/extlibs/bin/x64` 的 `openal32.dll`
-   具体方法：在 `SFML-2.5.1` 目录下，用 Release 选项编译 SFML 库，将生成的 `.a` 文件放入 `Snake/SFML/lib` ，生成的 `.dll` 文件以及 `openal32.dll` 放入 `Snake/application`  。随后在 `Snake` 目录下 build 即可。

-------------------
### 按照头文件介绍修改情况
-   SnakeNode.h

```cpp
namespace sfSnake
{
	static const sf::Color snake_color(255, 230, 0);

	// inherit from sf::Drawable and sf::Transformable
	// to support syntax window.draw(entity);
	class SnakeNode : public sf::Drawable, public sf::Transformable
	{
	public:
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

		// add rotation-related functions for rect_
		void setPosition(sf::Vector2f position);
		void setPosition(const float &x, const float &y);
		void setRotation(const float &angel);
		void setCircleColor(const sf::Color &color = snake_color);
		void setRectColor(const sf::Color &color = sf::Color::Black);
		void move(const float &xOffset, const float &yOffset);
		void rotate(const float &theta);
		void follow(const sfSnake::SnakeNode &node);

		sf::Vector2f getPosition() const;
		float getRotation() const;

		sf::FloatRect getBounds() const;

		const static float NodeRadius;
		const static float MoveDistance;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::CircleShape circle_;
		sf::RectangleShape rect_;	//rectangle of snake body
	};
}
```
-   修改：
    -   添加了旋转相关的函数，用于控制节点矩形的的转动方向。
    -   添加了设置节点颜色的函数，可以分别控制矩形和圆的颜色。
    -   添加了 `follow()` 函数，用于控制节点跟随另一个节点移动。
    -   对原静态成员 `Weight` `Height` 进行了修改。由于圆的半径与蛇移动的单位长度并不同，分别定义了相关常量 `NodeRadius` `MoveDistance` ，并设定其比例为 $3 : 4$

该类的对象在进入游戏界面以及蛇进行生长时创建，在退出游戏界面时被销毁。

-   Snake.h

```cpp
namespace sfSnake
{
	// add direction class
	// for mouse control
	class Direction
	{
	public:
		Direction(const float &angel = 0.f) : angle_(angel) {}
		void update(const sf::Vector2f &lhs, const sf::Vector2f &rhs);
		void update(const float &angel);
		float asAngle() const { return angle_; }
		sf::Vector2f asVector() const;
		const static Direction Left;
		const static Direction Right;
		const static Direction Up;
		const static Direction Down;
		// direction constants
	private:
		// in window coordinate
		// already applied vertical flip of y-axis
		// in angel instead of radian
		float angle_{0.f};
	};

	// for syntax window.draw(snake)
	class Snake : public sf::Drawable, public sf::Transformable
	{
	public:
		Snake();

		void handleInput(sf::RenderWindow &window);
		void update(const sf::Time &delta);
		bool checkFruitCollisions(std::vector<Fruit> &fruits);
		bool checkBodyBlock(const sf::FloatRect &bounds) const;
		float getAngel() const { return direction_.asAngle(); };
		bool hitSelf() const;

		unsigned getSize() const;

	private:
		void move();
		void grow(const Fruit &fruit);
		void checkEdgeCollisions();
		void checkSelfCollisions();
		void initNodes();
		void updateDirection(const sf::Vector2f &mousePos);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::SoundBuffer pickupBuffer_;
		sf::Sound pickupSound_;

		sf::SoundBuffer dieBuffer_;
		sf::Sound dieSound_;

		Direction direction_;
		bool hitSelf_;
		std::vector<SnakeNode> nodes_;

		sf::Texture headTexture_;
		sf::Sprite head_;

		static const int InitialSize;
		static const int CheckBegin;
	};
}
```
-   修改 `Direction`, 用于控制蛇头的转向
    -   此类通过 `update` 进行更新，通过 `asAngle` 输出角度值，保证输出的角度在 $[0, 360)$ 之间。并未输出弧度制，这是因为 `sf::Transformable` 中的 `rotate()` 接受角度值。通过 `asVector` 输出对应方向的单位向量。
    -   将原来的枚举类型定义为类内的静态成员变量，方便调用。
    -   已经应用了垂直翻转，因此不需要对 `y` 坐标进行额外的处理。只需要对类内的静态成员变量进行处理。
-   修改 `Snake`
    -   增加了 `Direction direction_` 以及相应的更新方向和获取方向的函数，用以支持鼠标控制。
    -   增加了 `checkBodyBlock()` ，用以检查蛇身是否与某个矩形相交。实际用于防止水果生成在蛇身上。 
    -   增加了 `sf::Sprite head_` ，用以绘制蛇头。
    -   增加了 静态成员变量 `CheckBegin` ，用于控制蛇身检测的起始位置。由于移动距离不等于节点的半径，且蛇头会进行旋转，需要在后几个节点进行撞击自身的检测。
该类的对象在进入游戏界面时创建，在退出游戏界面时被销毁。

-   Fruit.h

```cpp
namespace sfSnake
{
	class Fruit : public sf::Drawable, public sf::Transformable
	{
	public:
		Fruit(const sf::Vector2f position) : Fruit(position, sf::Color::Red) {}
		Fruit(const sf::Vector2f position, const sf::Color &color);
		void setFillColor(const sf::Color &color) { shape_.setFillColor(color); }
		static void initTexture();
		int bonusLength() const;
		sf::FloatRect getBounds() const;
		static const float Radius;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::CircleShape shape_;
		sf::Sprite sprite_;

		static const std::vector<sf::Vector2f> Scaler;
		static const std::vector<sf::IntRect> TextureRect;
		static std::vector<sf::Texture> Texture;
	};
	class Color : public sf::Color
	{
	public:
		static const sf::Color Brown;
	};
}
```
-   修改了 `Fruit` 类
    -   由于需要绘制不同颜色的水果，且不同颜色的水果提供的生长长度不同，增加了对应的设置颜色以及获取生长长度的函数。
    -   考虑利用 `sf::Sprite` 绘制水果，因此增加了 `sf::Sprite sprite_` 。因此还需要设置对应颜色水果对应参数。由于 `sf::Texture` 只有默认构造函数和复制构造函数，需要在静态成员函数 `initTexture()` 中进行初始化。
-   增加了 `sfSnake::Color` 类
    -   继承自 `sf::Color` ，用于提供棕色的静态成员变量。
该类的对象在进入游戏界面后创建，在退出游戏界面时被销毁。


-	World.h

```cpp
namespace sfSnake
{
    unsigned const gap{40};
    class World : public sf::Drawable, public sf::Transformable
    {
    public:
        World(const sf::Color &worldColor = sf::Color::Black, const sf::Color &gridColor = sf::Color::Transparent);
        void setWorldColor(const sf::Color &color);
        void setGridColor(const sf::Color &color);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::RectangleShape world_;
        sf::VertexArray grid_;
    };
}
```
-	增加了 `World` 类，用以控制游戏背景
	-	通过 `sf::RectangleShape` 绘制背景，通过顶点数组  `sf::VertexArray` 绘制网格。
	-	通过 `setWorldColor` `setGridColor` 设置背景颜色和网格颜色。
该类的对象在进入游戏界面后创建，在退出游戏界面时被销毁。

-   Game.h

```cpp
namespace sfSnake
{
	class Game
	{
	public:
		Game();

		void run();

		void handleInput();
		void update(sf::Time delta);
		void render();

		// slightly adjust width and height to make the game look better
		static const int Width = 960;
		static const int Height = 540;

		static std::shared_ptr<Screen> Screen;

	private:
		sf::RenderWindow window_;
		sf::Music bgMusic_;

		static sf::Time DeltaTime;
	};
}
```
-	增加了 `DeltaTime` 用于控制选择界面的动画效果。
	-	该项目只有一个 `Game` 的对象，生命周期为整个程序运行时期。其中的 `Screen` 为简易的单例模式。
该类的对象在程序开始后创建，在退出程序后被销毁。其生命周期贯穿整个程序运行时期。

-   Screen.h MenuScreen. GameOverScreen.h

未作修改。

-   OptionScreen.h

```cpp
namespace sfSnake
{
    // for option selection

    struct Option
    {
        sf::Color worldColor{sf::Color::Black};
        sf::Color gridColor{Color::Brown};
        size_t frameRate{10};
    };
    class OptionScreen : public Screen
    {
    public:
        OptionScreen();
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;
        const Option &getOption() const;
        void setWorldColor(const sf::Color &color);
        void setGridColor(const sf::Color &color);
        void setFrame(const size_t &frame);

    private:
        sf::Text background_;
        sf::Text gridColor_;
        sf::Text difficulty_;
        sf::Text start_;
        sf::Font font_;
        Option option_;
    };
}
```
-	新增了 `struct Option` ，用于存储选项的信息。
-	新增了 `OptionScreen` 类，用于获取选项并传递给 `GameScreen` 类
	-	利用三个 `setter` 函数设置对应的选项。利用 `getOption` 函数获取选项。
该类在进入设置界面时创建，在退出设置界面进入游戏界面时销毁。

-	GameScreen.h

```cpp
namespace sfSnake
{
	class GameScreen : public Screen
	{
	public:
		GameScreen();
		GameScreen(const Option &option, sf::RenderWindow &window);

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;
		void generateFruit();

	private:
		Snake snake_;
		std::vector<Fruit> fruit_;
		World world_;
		size_t score_{0};
	};
	sf::Vector2f generatePos(Snake &snake_);
	sf::Color generateColor();
}
```
-	修改了 `GameScreen` 类
	-	将生成水果中的随机数产生过程封装成函数 `generatePos` `generateColor` ，分别用于生成水果的位置和颜色。
	-	增加了 `score_` 用于记录分数。考虑到不同水果的增加长度不同，因此分数设定为 吃掉的水果的数量 $\times 5$ ，而不是蛇的长度。
该类在进入游戏界面时创建，在退出游戏界面进入结算界面时销毁。

-------------------
### 按照功能介绍修改情况
-   移动方式
增加了鼠标控制蛇移动的功能：在游戏界面中的某个位置单击鼠标左键，蛇会朝着这个方向移动。可以按住左键来实现蛇的连续移动。如果转弯幅度过大，可能导致死亡判定。

修改思路：原作者设置了四个方向的枚举类 `Direction`，故可以直接实现这个控制方向的类，然后将枚举类换成类内静态成员即可兼容。这个 `Direction` 类储存在 `Snake` 类内，用于控制蛇头的转向。在 `handleInput` 中，如果检测到鼠标左键按下，就利用蛇头的位置和鼠标所在的位置更新 `Direction` 类的方向。同时由于新的 `Direction` 类与原来的枚举类相互兼容，因此修改后仍然可以用方向键控制蛇的移动。

核心代码：（修改部分）
```cpp
void Direction::update(const sf::Vector2f &begin, const sf::Vector2f &end)
{
	if (begin.x == end.x)
	{
		if (begin.y > end.y)
			angle_ = Direction::Down.angle_;
		else if (begin.y < end.y)
			angle_ = Direction::Up.angle_;
	}
	else
	{
		angle_ = atan2(end.y - begin.y, end.x - begin.x) * 180.f / acos(-1);
		if (angle_ < 0)
			angle_ += 360.f;
	}
}
void Snake::handleInput(sf::RenderWindow &window)
{
	if ...
		...
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		updateDirection(sf::Vector2f(mousepos.x, mousepos.y));
	}
}
void Snake::updateDirection(const sf::Vector2f &mousePos)
{
	static const float maxdelta = 30.f;
	float origin = direction_.asAngle();
	direction_.update(nodes_.front().getPosition(), mousePos);
	float delta = direction_.asAngle() - origin;

	// limit angle variation to 30 degrees a frame in case 
	// of too large mouse movement
	// avoid most cases of instant death
	if (delta >= 0.f)
	{
		if (delta <= maxdelta && delta > 360.f - maxdelta)
		{
			direction_.update(origin);
		}
		else if (delta > maxdelta && delta <= 180.f)
		{
			direction_.update(origin + maxdelta);
		}
		else if (delta > 180.f && delta < 360.f - maxdelta)
		{
			direction_.update(origin - maxdelta);
		}
	}
	else
	{
		if (delta >= -maxdelta && delta < maxdelta - 360.f)
		{
			direction_.update(origin);
		}
		else if (delta < -maxdelta && delta >= -180.f)
		{
			direction_.update(origin - maxdelta);
		}
		else if (delta < -180.f && delta > maxdelta - 360.f)
		{
			direction_.update(origin + maxdelta);
		}
	}
}

```

-	水果颜色、长度增量、数量和渲染方式：
为水果添加了颜色，长度增量并通过 `sf::Sprite` 渲染对应的图片。其中红色、绿色、蓝色、棕色、黑色水果分别对应的概率是 $\text{1/4}$ 、 $\text{1/4}$ 、 $\text{1/4}$ 、 $\text{1/8}$ 、 $\text{1/8}$ ，对应的长度增量分别是 $\text{3}$ 、 $\text{2}$ 、 $\text{1}$ 、 $\text{0}$ 、 $\text{0}$ ，对应的图片分别为苹果、青柠、蓝莓、椰子、黑莓。

原作者利用 `std::vector` 容器维护水果，故可较容易的修改水果的数量。根据游戏界面的大小调整水果个数为 $\text{10}$ 个

将水果颜色和位置的随机函数封装为了静态函数。

核心代码：（修改部分）
```cpp
sf::Vector2f generatePos(Snake &snake_)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::NodeRadius * 2);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::NodeRadius * 2);
	sf::FloatRect bound;
	// assure there's no collision between fruit and snake
	do
	{
		bound = sf::FloatRect(xDistribution(engine), yDistribution(engine), Fruit::Radius * 2, Fruit::Radius * 2);
	} while(snake_.checkBodyBlock(bound) == true);
	return sf::Vector2f(bound.left, bound.top);
}
sf::Color generateColor()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_real_distribution<float> colorDistribution(0.f, 1.f);
	float r = colorDistribution(engine);
	if(r >= 0.f && r < 0.125f)
		return sf::Color::Black;
	else if(r >=0.125f && r < 0.25f)
		return Color::Brown;
	else if(r >= 0.25f && r < 0.5f)
		return sf::Color::Red;
	else if(r >= 0.5f && r < 0.75f)
		return sf::Color::Blue;
	else if(r >= 0.75f && r < 1.f)
		return sf::Color::Green; 
	
	// if the random number is out of range, return transparent
	return sf::Color::Transparent;
}
void GameScreen::generateFruit()
{
	// note : without the :: , the compiler won't recognize the function
	fruit_.emplace_back(::generatePos(snake_), ::generateColor());
}
```
-	精灵版本的贪吃蛇
利用圆和黑色矩形绘制蛇身，头部使用图片，利用 `sf::Sprite` 进行绘制。由于需要控制黑色矩形的转动，需要在 `SnakeNode` 中补充对应的与转动相关的函数。头节点的转动角可以认为和移动方向一致，由 `Direction` 类给出，无需重新定义。
> 蛇头的素材来自贪吃蛇大作战

核心代码：（修改部分）
```cpp	
namespace sfSnake
{
	class SnakeNode : public sf::Drawable, public sf::Transformable
	{
	public:
		// add rotation-related functions for rect_
		...
		void setRotation(const float &angel);
		void setCircleColor(const sf::Color &color = snake_color);
		void setRectColor(const sf::Color &color = sf::Color::Black);
		void rotate(const float &theta);
		void follow(const sfSnake::SnakeNode &node);

		...
		float getRotation() const;


		const static float NodeRadius;
		const static float MoveDistance;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::CircleShape circle_;
		sf::RectangleShape rect_;	//rectangle of snake body
	};
	void Snake::initNodes()
	{
	
	headTexture_.loadFromFile("Textures/head.png");
	head_.setTexture(headTexture_);
	head_.setOrigin(SnakeNode::NodeRadius, SnakeNode::NodeRadius);
	head_.setPosition(Game::Width / 2, Game::Height / 2);
	...
	}
}
```	

-	背景、网格
二者都包含在 `World` 类中。利用矩形绘制背景，利用 SFML 库提供的顶点数组 `sf::VertexArray` 设计网格。

核心代码：
```cpp
namespace sfSnake
{
    unsigned const gap{40};
    class World : public sf::Drawable, public sf::Transformable
    {
    public:
        World(const sf::Color &worldColor = sf::Color::Black, const sf::Color &gridColor = sf::Color::Transparent);
        void setWorldColor(const sf::Color &color);
        void setGridColor(const sf::Color &color);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::RectangleShape world_;
        sf::VertexArray grid_;
    };
}
World::World(const sf::Color &worldColor, const sf::Color &gridColor)
{
    world_.setFillColor(worldColor);
    world_.setSize(sf::Vector2f(Game::Width, Game::Height));
    grid_.setPrimitiveType(sf::Lines);
    const int xnumber = Game::Width / gap - 1;
    const int ynumber = Game::Height / gap - 1;
    grid_.resize(2 * xnumber + 2 * ynumber);
    sf::Vertex *line = &(grid_[0]);
    for (int i = 0; i < xnumber; ++i)
    {
        line[2 * i].position = sf::Vector2f(gap * (i + 1), 0);
        line[2 * i].color = gridColor;
        line[2 * i + 1].position = sf::Vector2f(gap * (i + 1), Game::Height);
        line[2 * i + 1].color = gridColor;
    }
    line = &(grid_[2 * xnumber]);
    for (int i = 0; i < ynumber; ++i)
    {
        line[2 * i].position = sf::Vector2f(0, gap * (i + 1));
        line[2 * i].color = gridColor;
        line[2 * i + 1].position = sf::Vector2f(Game::Width, gap * (i + 1));
        line[2 * i + 1].color = gridColor;
    }
}
```

-	选择界面（`OptionScreen`）
上面已经制作好了素材，自然需要一个选择界面来选择素材，且要方便玩家。故类似 `MenuScreen` 类新增一个 `OptionScreen` 类，实现对背景、网格、游戏难度的选择。
在选择界面时可以通过对应按键选择对应的背景、网格、游戏难度。在玩家做出选择后，对应的文字会变为选择的颜色以给与提示。

背景颜色：W: 白色 E: 黑色 R:棕色

网格颜色：A: 白色 S: 黑色 D:棕色 F: 没有网格（透明）

游戏难度：Z: 幼虫（简单） X: 蜈蚣（中等） C: 蛇（困难）（通过改变帧率）

核心代码：详见 `OptionScreen.cpp` 和 `OptionScreen.h` 文件

------------------
一些其他修改：
-	将原作者设计的实体的 `render()` 改为 `draw()`：通过继承 `sf::Transformable` 和 `sf::Drawable` 类，可以 override `draw()` 函数以提供 `window.draw(entity)` 语义。而对于几个窗口类仍然使用 `render()` 函数。
-	将部分较短函数，尤其是 `SnakeNode` 类中的函数设置为内联函数，以提高效率。
-	修改了拾取音频的格式，使其能够正常播放。
-	将分数改为与吃几个水果有关，而不是与蛇身长度有关。