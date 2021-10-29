#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "colors.h"
#include "imgui_raii_wrapper.h"

void draw_table() {

  using colors::Green;
  using colors::Red;

  irw::Windowzita mockup{"Mockup Table"};
  irw::TabBar tab_bar{"TabBar"};
  if (irw::TabItem tab_item{"Accounts & Categories"}) {
    auto table = irw::Table::Builder{}.with_id("Table")
      .with_number_of_columns(4)
      .with_headers("Account/Category", "Remaining Budget", "Change", "Total")
      .add_row("Assets", "", irw::Text{"$-778.32", Red}, "$29,754.72")
      .add_row("|- Cash", "", irw::Text{"$-2.85", Red}, "$236.30")
      .add_row("|- Checking Account", "", irw::Text{"$-634.99", Red}, "$7,327.01")
      .add_row("|- Euro Account", "", irw::Text{"-120.00 EUR", Red}, "5,403.00 EUR")
      .add_row("|- Investment Account", "", "0 CNY", "20,400.00 CNY")
      .add_row("|- Savings Account", "", "$0.00", "$12,800.00")
      .add_row("Liabilities", "", irw::Text{"$-200.00", Green}, "$11,400.00")
      .add_row("|- Car Loan", "", irw::Text{"$-200.00", Green}, "$11,400.00")
      .add_row("Incomes", "-", "$0.00", "$18,853.50")
      .add_row("|- Other", "-", "$0.00", "$5,853.50")
      .add_row("|- Salary", "-", "$0.00", "$13,000.00")
      .add_row("Expenses", irw::Text{"$226.67 of $460.00", Green}, irw::Text{"$578.32", Red}, "$4,532.67")
      .add_row("|- Bills", "-", irw::Text{"$30.00", Red}, "$3,092.00")
      .add_row("|- Clothing", irw::Text{"$-40.48 of $100.00", Red}, irw::Text{"$140.48", Red}, "$949.48")
      .add_row("|- Groceries", irw::Text{"$74.15 of $160.00", Green}, irw::Text{"$85.85", Red}, "$155.20")
      .add_row("|- Leisure", irw::Text{"$193.00 of $200.00", Green}, irw::Text{"$7.00", Red}, "$21.00")
      .add_row("|- Other", "-", irw::Text{"$314.99", Red}, "$314.99")
      .build();
  }
  if (irw::TabItem tab_item{"Expenses"}) {
    irw::Text("Manga");
  }
  if (irw::TabItem tab_item{"Incomes"}) {
    irw::Text("My income is €100k (daily)");
  }
  if (irw::TabItem tab_item{"Transfers"}) {
    irw::Text("I transfered everything to the manga store");
  }
  if (irw::TabItem tab_item{"Securities"}) {
    irw::Text("NullPointerException");
  }
  if (irw::TabItem tab_item{"Schedule"}) {
    irw::Text("Minha criatividade já se acabou");
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "Cash Overflow");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  sf::CircleShape shape{100.F};
  shape.setFillColor(sf::Color::Cyan);
  shape.setPosition(sf::Vector2f{500.0, 350.0});

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    draw_table();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
