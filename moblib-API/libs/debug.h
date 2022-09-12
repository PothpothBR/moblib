#ifndef DEBUG_H
#define DEBUG_H

const char* format_strings(const char* string, int size) {

	int ssize = 0;

	for (char i = ' '; i != '\0'; i = string[ssize++]);

	char* buffer = new char[size];

	for (int i = 0; i < ssize-1; i++) buffer[i] = string[i];
	buffer[ssize - 1] = '\"';
	for (int i = ssize; i < size - 1; i++) buffer[i] = ' ';
	buffer[size - 1] = '\0';

	return buffer;

}

// mostra as definicoes do core, mostradas integralmente
void debug_core(Core* tmp) {

	cout << endl << endl;

	cout << " #-------------[objects buffer size]------------\n";
	cout << " | [objects: " << tmp->_objects->size_object << "]\n";
	cout << " #----------------------------------------------\n\n\n";

	cout << " <<objects>>\n";
	for (int i = 0; i < tmp->_objects->size_object; i++) {

		cout << " [" << i << "] object: \"" << *tmp->_objects->_object[i] << "\"\n";
		for (int e = 0; e < tmp->_objects->_property[i].id_size; e++) {

			const char* name = " ";

			switch (*tmp->_objects->_property[i].buffer_id[e]) {

			case 0:
				name = "animation";
				break;
			case 1:
				name = "moviment";
				break;

			}

			cout << "    [" << e << "] properties: \"" << name << "\"\n";
			for (int j = 0; j < tmp->_objects->_property[i].link_size[e]; j++) {

				cout << "        [" << j << "] name: \"" << (int)tmp->_objects->_property[i].buffer_link[e][j] << "\" - \"" << *tmp->_objects->_property[i].buffer_link[e][j] << "\"\n";

			}

		}
	}
	cout << endl;

	cout << " #-----------[animations buffer size]-----------\n";
	cout << " | [instances: " << tmp->_animation->anim_instance_size << "]\n";
	cout << " | [animations: " << tmp->_animation->anim_size << "]\n";
	cout << " | [ids: " << tmp->_animation->anim_ids->id_size << "]\n";
	cout << " #----------------------------------------------\n\n\n";

	cout << " <<animations by instance>>\n";
	for (int i = 0; i < tmp->_animation->intern_ids->id_size; i++) {

		cout << " [" << i << "] instance: \"" << (int)tmp->_animation->_instance[i] << "\" - \"" << *tmp->_animation->intern_ids->buffer_id[i] << "\"\n";

		for (int e = 0; e < tmp->_animation->intern_ids->link_size[i]; e++) {

			cout << "    [" << e << "] animation: \"" << (int)*tmp->_animation->intern_ids->buffer_link[i][e] << "\" - \"" << **tmp->_animation->intern_ids->buffer_link[i][e] << "\"\n";

		}
	}
	cout << endl;

	cout << " <<animations by position>>\n";
	for (int i = 0; i < tmp->_animation->anim_ids->id_size; i++) {

		cout << " [" << i << "] animation: \"" << (int)*tmp->_animation->anim_ids->buffer_id[i] << "\" - \"" << **tmp->_animation->anim_ids->buffer_id[i] << "\"\n";

	}
	cout << endl;

	cout << " <<animations by instance and atributes>>\n";
	for (int i = 0; i < tmp->_animation->intern_ids->id_size; i++) {

		cout << " [" << i << "] instance: \"" << (int)tmp->_animation->_instance[i] << "\" - \"" << *tmp->_animation->intern_ids->buffer_id[i]
			<< "\" <|range: " << tmp->_animation->_instance[i]->rangeOfCells
			<< " | direction:" << tmp->_animation->_instance[i]->direction
			<< " | delay:" << tmp->_animation->_instance[i]->delay
			<< " | fps:" << tmp->_animation->_instance[i]->FPS
			<< " | step:" << tmp->_animation->_instance[i]->step
			<< "|>" <<  "\n";

		for (int e = 0; e < tmp->_animation->intern_ids->link_size[i]; e++) {

			cout << "    [" << e << "] animation: \"" << (int)*tmp->_animation->intern_ids->buffer_link[i][e] << "\" - \"" << format_strings(**tmp->_animation->intern_ids->buffer_link[i][e], 10)
				<< " <| flip:" << tmp->_animation->getAnimation(*tmp->_animation->intern_ids->buffer_link[i][e])->flip
				<< " | time:" << *tmp->_animation->getAnimation(*tmp->_animation->intern_ids->buffer_link[i][e])->time->time
				<< " |start: " << tmp->_animation->getAnimation(*tmp->_animation->intern_ids->buffer_link[i][e])->start
				<< " | end:" << tmp->_animation->getAnimation(*tmp->_animation->intern_ids->buffer_link[i][e])->end
				<< " | index:" << tmp->_animation->getAnimation(*tmp->_animation->intern_ids->buffer_link[i][e])->index
				<< "|>" << "\n";

		}
	}
	cout << endl;
}

#endif
