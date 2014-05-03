using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IrrlichtLime;
using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace _20.ManagedLights
{
    class MyLightManager : LightManager
    {
        enum LightManagementMode
        {
            NoManagement,
            LightsNearestNode,
            LightsInZone
        }

        LightManagementMode mode;
        LightManagementMode requestedMode;

        SceneManager smgr;
        SceneNode[] sceneLightList;
        SceneNodeRenderPass currentRenderPass;
        SceneNode currentSceneNode;

        public MyLightManager(SceneManager smgr)
            : base()
        {
            this.smgr = smgr;

            mode = LightManagementMode.NoManagement;
            requestedMode = LightManagementMode.NoManagement;

            sceneLightList = null;
            currentRenderPass = SceneNodeRenderPass.None;
            currentSceneNode = null;

            this.OnPreRender += new PreRenderEventHandler(MyLightManager_OnPreRender);
            this.OnPostRender += new PostRenderEventHandler(MyLightManager_OnPostRender);
            this.OnRenderPassPreRender += new RenderPassPreRenderEventHandler(MyLightManager_OnRenderPassPreRender);
            this.OnRenderPassPostRender += new RenderPassPostRenderEventHandler(MyLightManager_OnRenderPassPostRender);
            this.OnNodePreRender += new NodePreRenderEventHandler(MyLightManager_OnNodePreRender);
        }

        public bool MyLightManager_OnEvent(Event evnt)
        {
            bool handled = false;

            if (evnt.Type == EventType.Key && evnt.Key.PressedDown)
            {
                handled = true;
                switch (evnt.Key.Key)
                {
                    case KeyCode.Key1:
                        requestedMode = LightManagementMode.NoManagement;
                        break;
                    case KeyCode.Key2:
                        requestedMode = LightManagementMode.LightsNearestNode;
                        break;
                    case KeyCode.Key3:
                        requestedMode = LightManagementMode.LightsInZone;
                        break;
                    default:
                        handled = false;
                        break;
                }

                if (requestedMode == LightManagementMode.NoManagement)
                    smgr.LightManager = null; // Show that it's safe to register the light manager
                else
                    smgr.LightManager = this;
            }

            return handled;
        }

        void MyLightManager_OnPreRender(SceneNode[] lightList)
        {
            // Update the mode; changing it here ensures that it's consistent throughout a render
            mode = requestedMode;

            // Store the light list. I am free to alter this list until the end of OnPostRender().
            this.sceneLightList = lightList;
        }

        void MyLightManager_OnPostRender()
        {
            // Since light management might be switched off in the event handler, we'll turn all
            // lights on to ensure that they are in a consistent state. You wouldn't normally have
            // to do this when using a light manager, since you'd continue to do light management
            // yourself.
            foreach (SceneNode node in sceneLightList)
                node.Visible = true;
        }

        void MyLightManager_OnRenderPassPreRender(SceneNodeRenderPass renderPass)
        {
            // I don't have to do anything here except remember which render pass I am in.
            currentRenderPass = renderPass;
        }

        void MyLightManager_OnRenderPassPostRender(SceneNodeRenderPass renderPass)
        {
            // I only want solid nodes to be lit, so after the solid pass, turn all lights off.
            if (renderPass == SceneNodeRenderPass.Solid)
                foreach (SceneNode node in sceneLightList)
                    node.Visible = false;
        }

        struct LightDistanceElement : IComparable<LightDistanceElement>
        {
            public SceneNode node;
            public float distance;

            public LightDistanceElement(SceneNode node, float distance)
            {
                this.node = node;
                this.distance = distance;
            }

            public int CompareTo(LightDistanceElement other)
            {
                return distance.CompareTo(other.distance);
            }
        }

        void MyLightManager_OnNodePreRender(SceneNode node)
        {
            currentSceneNode = node;

            // This light manager only considers solid objects, but you are free to manipulate
            // lights during any phase, depending on your requirements.
            if (currentRenderPass != SceneNodeRenderPass.Solid)
                return;

            // And in fact for this example, I only want to consider lighting for cube scene
            // nodes.  You will probably want to deal with lighting for (at least) mesh /
            // animated mesh scene nodes as well.
            if (node.Type != SceneNodeType.Cube)
                return;

            if (mode == LightManagementMode.LightsNearestNode)
            {
                // This is a naive implementation that prioritises every light in the scene
                // by its proximity to the node being rendered.  This produces some flickering
                // when lights orbit closer to a cube than its 'zone' lights.
                Vector3Df nodePosition = node.AbsolutePosition;

                // Sort the light list by prioritising them based on their distance from the node
                // that's about to be rendered.
                List<LightDistanceElement> sortingList = new List<LightDistanceElement>(sceneLightList.Length);

                foreach (SceneNode lightNode in sceneLightList)
                {
                    float distance = lightNode.AbsolutePosition.GetDistanceFromSQ(nodePosition);
                    sortingList.Add(new LightDistanceElement(lightNode, distance));
                }

                sortingList.Sort();

                // The list is now sorted by proximity to the node.
                // Turn on the three nearest lights, and turn the others off.
                for (int i = 0; i < sortingList.Count; i++)
                    sortingList[i].node.Visible = i < 3;
            }
            else if (mode == LightManagementMode.LightsInZone)
            {
                // Empty scene nodes are used to represent 'zones'.  For each solid mesh that
                // is being rendered, turn off all lights, then find its 'zone' parent, and turn
                // on all lights that are found under that node in the scene graph.
                // This is a general purpose algorithm that doesn't use any special
                // knowledge of how this particular scene graph is organised.
                foreach (SceneNode lightNode in sceneLightList)
                {
                    LightSceneNode light = lightNode as LightSceneNode;
                    if (light != null)
                    {
                        if (light.LightData.Type != LightType.Directional)
                            light.Visible = false;
                    }
                }
                SceneNode parentNode = findZone(node);
                if (parentNode != null)
                    turnOnZoneLights(parentNode);
            }
            
        }

        // Find the empty scene node that is the parent of the specified node
        SceneNode findZone(SceneNode node)
        {
            if (node == null)
                return null;
            if (node.Type == SceneNodeType.Empty)
                return node;
            return findZone(node.Parent);
        }

        // Turn on all lights that are children (directly or indirectly) of the
        // specified scene node.
        void turnOnZoneLights(SceneNode node)
        {
            foreach (SceneNode child in node.Children)
                if (child.Type == SceneNodeType.Light)
                    child.Visible = true;
                else // Assume that lights don't have any children that are also lights
                    turnOnZoneLights(child);
        }
    }
}
