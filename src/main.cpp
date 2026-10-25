#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Создаем аккуратный текстовый блок для отображения на экране смартфона
class MobileHUD : public cocos2d::CCNode {
public:
    cocos2d::CCLabelBMFont* m_label;

    bool init() override {
        if (!CCNode::init()) return false;

        // Создаем текст. "chatFont.fnt" — стандартный тонкий шрифт GD, который не лагает
        m_label = cocos2d::CCLabelBMFont::create("Frame Window: 0", "chatFont.fnt");
        m_label->setScale(0.7f); // Оптимальный размер для экрана телефона
        m_label->setAnchorPoint({0.0f, 1.0f});
        
        // Позиция: отступаем 15 пикселей слева и 40 сверху, чтобы не перекрывать процент прохождения
        m_label->setPosition({15.0f, 300.0f}); 
        m_label->setColor({0, 255, 0}); // Зеленый цвет по умолчанию
        
        this->addChild(m_label);
        return true;
    }

    static MobileHUD* create() {
        auto ret = new MobileHUD();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    void updateFrameDisplay(int frames) {
        std::string text = "Frame Window: " + std::to_string(frames);
        m_label->setString(text.c_str());
        
        // Меняем цвет в зависимости от жесткости тайминга
        if (frames <= 1) {
            m_label->setColor({255, 0, 0}); // Красный (Frame Perfect!)
        } else if (frames <= 3) {
            m_label->setColor({255, 165, 0}); // Оранжевый (Сложно)
        } else {
            m_label->setColor({0, 255, 0}); // Зеленый (Просто)
        }
    }
};

// Внедряемся в игровой слой, чтобы прикрепить наш текст к экрану
class $modify(MyPlayLayer, PlayLayer) {
    MobileHUD* m_hud = nullptr;

    bool init(GJGameLevel* level, bool useReplay, bool dontRunActions) {
        if (!PlayLayer::init(level, useReplay, dontRunActions)) return false;

        // Создаем HUD и добавляем его поверх уровня (z-order 999)
        auto hud = MobileHUD::create();
        this->addChild(hud, 999);
        m_fields->m_hud = hud;

        return true;
    }
};

// Перехватываем нажатия пальцем по экрану
class $modify(MyPlayerObject, PlayerObject) {
    void pushButton() {
        PlayerObject::pushButton();

        auto playLayer = PlayLayer::get();
        if (!playLayer) return;

        // Получаем текущую дельту времени игры
        float lastDelta = playLayer->m_gameState.m_lastDeltaTime;
        float frameInterval = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();

        // Считаем разницу в кадрах. Если дельта нулевая — это чистый 0-1 фрейм
        int frameDelta = 0;
        if (frameInterval > 0) {
            frameDelta = static_cast<int>(lastDelta / frameInterval);
        }

        // Обновляем текст на экране
        if (auto myLayer = reinterpret_cast<MyPlayLayer*>(playLayer)) {
            if (myLayer->m_fields->m_hud) {
                myLayer->m_fields->m_hud->updateFrameDisplay(frameDelta);
            }
        }
    }
};

