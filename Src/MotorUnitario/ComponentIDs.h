/*
This enum controls de order of updates of components in every gameObject, 
	except those defined by the user, which always update the latest

It's recommendable to keep an order when introducing a new Component to the enum 
	(Eg. first graphic-related objects, then audio, etc)
*/

namespace ComponentId {
	enum ComponentId : unsigned int {
		Transform = 0,
		ImageRender,
		RenderObject,
		Animator,
		LightComponent,
		ParticleSystem,
		Camera,
	
		Rigidbody,
		Collider,
	
		AudioSource,
		ListenerComponent,

		ButtonComponent,

		//from this point, every id forward is of a component defined by the user
		__StartPointUser__
	};
}