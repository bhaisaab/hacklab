class CreateRooms < ActiveRecord::Migration
  def change
    create_table :rooms do |t|
      t.string :name
      t.integer :capacity
      t.integer :floor
      t.string :building

      t.timestamps
    end
  end
end
